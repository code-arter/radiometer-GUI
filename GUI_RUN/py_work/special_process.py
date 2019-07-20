#coding: utf-8
import os
import sys
import re
import time
import shutil
import subprocess
import numpy
import math
import copy
import logging
from atmos_csv.main import UserdDefine

def change_aerosol_haze(value):
    value_type = value[0].split(" ")[1]
    if value_type == "rural-type-aerosols":
        type_int = 1
    elif value_type == "maritime-type-aerosols":
        type_int = 2
    elif value_type == "urban-type-aerosols":
        type_int = 5
    elif value_type == "tropospheric-type-aerosols":
        type_int = 6
    return ["aerosol_haze %s" % type_int]

def change_aerosol_season(value):
    value_type = value[0].split(" ")[1]
    if value_type == "spring-summer-profile":
        type_int = 1
    elif value_type == "fall-winter-profile":
        type_int = 2
    return ["aerosol_season %s" % type_int]

def change_aerosol_vulcan(value):
    value_type = value[0].split(" ")[1]
    if value_type == "background-aerosols":
        type_int = 1
    elif value_type == "moderate-vulcanic-aerosols":
        type_int = 2 
    elif value_type == "high-vulcanic-aerosols":
        type_int = 3
    elif value_type == "extreme-vulcanic-aerosols":
        type_int = 4
    return ["aerosol_vulcan %s" % type_int]


def create_grid_file(wavelength_list):
    if not wavelength_list:
        return []
    name, wave_start, wave_end, wave_step = wavelength_list[0].split(' ')
    wave_list = numpy.arange(float(wave_start), float(wave_end) + 0.1, float(wave_step)).tolist()
    wave_str_list = ["%s 1" % str(wave) for wave in wave_list]
    wave_grid_str = '\n'.join(wave_str_list)
    key_id = time.time()
    wave_grid_file = os.path.join("wavelength_grid", "wave_grid_file-%s" % key_id)
    with open(wave_grid_file, "w") as fp:
        fp.write(wave_grid_str)
    return ["wavelength_grid_file %s" % wave_grid_file]

def create_grid_file_by_count(wavecount):
    name, start, end, step = wavecount[0].split(" ")
    wavecount_list = numpy.arange(float(start), float(end) + 0.1, -float(step)).tolist()
    wavelength_list = [10000.0 / wavecount * 1000 for wavecount in wavecount_list]
    str_wavelength_list = ['%s 1' % str(wavelength) for wavelength in wavelength_list]
    wave_grid_path = "wavelength_grid/wave_grid_file.tmp"
    with open(wave_grid_path, "w") as fp:
        fp.write("\n".join(str_wavelength_list))
    return ["wavelength_grid_file %s" % wave_grid_path]



def set_option_multi_value(Options, key, data_list):
    if key not in Options:
        return
    length = len(data_list)
    obj = Options[key]
    input_list = obj.inputs
    for index, input_obj in enumerate(input_list):
        input_obj.SetValueNew(data_list[0][index].decode("utf-8"))
    for index in range(length - 1):
        child_obj = obj.AddChild()
        for idx, input_obj in enumerate(child_obj.inputs):
            input_obj.SetValueNew(data_list[index+1][idx].decode("utf-8"))


def getRunMode(Options):
    if "global_mode" in Options:
        global_mode = Options["global_mode"].GetWriteValue()[0].split(' ')[1]
    else:
        global_mode = u"单点模式"
    if global_mode == u"单点模式":
        return "normal"
    else:
        return "user_define"
    return global_mode


def change_um_to_nm(name, input_list=[]):
    if not input_list:
        return []
    value_list = input_list[0].split(' ')
    for index, val in enumerate(value_list):
        value_list[index] = str(float(val) * 1000) if val != name else val
    return [' '.join(value_list)]

def convert_cloud_to_file(cloud_name, value_list):
    write_list = []
    if not value_list:
        return []
    head_list = [None, '0.000', '0']
    set_list = value_list[0].split('\n')
    input_type = None
    for index, cloud_set in enumerate(set_list[::-1]):
        set_name, input_type, cloud_height, cloud_thick, cloud_lwc, cloud_r = cloud_set.split(' ')
        head_list[0] = str(float(cloud_height) + float(cloud_thick))
        tmp_str = "  ".join(head_list)
        write_list.append(tmp_str)

        tmp_str = "  ".join([cloud_height, cloud_lwc, cloud_r])
	write_list.append(tmp_str)
    tgt_file = "./cloud/%s.tmp" % cloud_name
    with open(tgt_file, 'w') as fp:
        fp.write('\n'.join(write_list))
    if cloud_name == "ic_set":
        ret = ["ic_file %s %s" % (input_type, tgt_file)]
    elif cloud_name == "wc_set":
        ret = ["wc_file %s %s" % (input_type, tgt_file)]
    return ret 

def process_special_general_dict(general_dict):
    multi_choice = general_dict.get("multi_choice", "")
    if not multi_choice:
        return ""
    select_choice = multi_choice[0].split(" ")[1]

    if select_choice == u"观测方位角":
        umu_val = general_dict["angle_of_pitch"][0].split(" ")[1]
        dis_val = general_dict["distance"][0].split(" ")[1]
        general_dict["angle_of_pitch"] = ["angle_of_pitch %s %s 1" % (umu_val, umu_val)]
        general_dict["distance"] = ["distance %s %s 1" % (dis_val, dis_val)]
    elif select_choice == u"观测俯仰角":
        phi_val = general_dict["azimuth_angle"][0].split(" ")[1]
        dis_val = general_dict["distance"][0].split(" ")[1]
        general_dict["azimuth_angle"] = ["azimuth_angle %s %s 1" % (phi_val, phi_val)]
        general_dict["distance"] = ["distance %s %s 1" % (dis_val, dis_val)]
    elif select_choice == u"距离":
        umu_val = general_dict["angle_of_pitch"][0].split(" ")[1]
        phi_val = general_dict["azimuth_angle"][0].split(" ")[1]
        general_dict["azimuth_angle"] = ["azimuth_angle %s %s 1" % (phi_val, phi_val)]
        general_dict["angle_of_pitch"] = ["angle_of_pitch %s %s 1" % (umu_val, umu_val)]
    general_dict.pop("multi_choice")

def process_zout_and_altitude(general_dict):
    if "zout" not in general_dict:
        return

    zout = general_dict["zout"][0].split(" ")[1]
    altitude_val = general_dict.get("altitude", None)
    if float(zout) > 120:
        zout = "toa"
    elif altitude_val is not None:
        altitude = altitude_val[0].split(" ")[1]
        zout = float(zout) - float(altitude)
    else:
        zout = zout
    general_dict["zout"] = ["zout %s" % str(zout)]

def getQtInputDict(data_dict):

    general_options = ["global_mode", "direction", "main_wave", "main_wave",
                       "general_location", "sight_height", "multi_choice", "angle_of_pitch", "azimuth_angle", "distance", "day_of_year"]
    data=[]
    general_dict = {}
    modify_attr_dict = {"wavecount": [], "wavelength": [], "output_quantity": [], "output_process": []}
    atmos_list = ["gas_file", "pressure_file", "temperature_file", "latitude_file"]
    atmos_file_list = []
    omit_list = ["general_location"]
    other_dict = {}
    phi_value = None
    atmosphere_define = ""
    ic_set = ""
    wc_set = ""
    ic_file = ""
    wc_file = ""

    source_type = ""
    source_file = ""
    source_unit = ""
    main_wave = ""

    for option_name, option_val in data_dict.items():
        value = option_val
        if option_name in omit_list:
            # attr in omit tabs, shoule be deleted
            continue
        if option_name == "main_wave":
            main_wave = value
            continue
        elif option_name in general_options:
            # new tab, should be specialy processed
            general_dict[option_name] = value
        elif option_name in modify_attr_dict:
            # attr in other tabs, shoule be redefined
            modify_attr_dict[option_name] = value
        elif option_name in atmos_list:
            atmos_file_list.append(value)
        elif option_name == "ic_set":
            ic_set = value
            continue
        elif option_name == "wc_set":
            wc_set = value
            continue
        elif option_name == "ic_file":
            ic_file = value
            continue
        elif option_name == "wc_file":
            wc_file = value
            continue
        elif option_name == "source_type":
            source_type = value
            continue
        elif option_name == "source_file":
            source_file = value
            continue
        elif option_name == "source_unit":
            source_unit = value
            continue
        elif option_name == "aerosol_haze":
            other_dict["aerosol_haze"] = change_aerosol_haze(value)
        elif option_name == "aerosol_season":
            other_dict["aerosol_season"] = change_aerosol_season(value)
        elif option_name == "aerosol_vulcan":
            other_dict["aerosol_vulcan"] = change_aerosol_vulcan(value)
        elif option_name == "atmosphere_define":
            atmosphere_define = value[0].split(" ")[1]
        else:
            # attr in other tabs, should not be changed
            other_dict[option_name] = value
    if len(atmos_file_list) < 4:
        return {}, "Failed: Lack of atmosphere_file"

    #check general_dict
    is_success, lack_fields = check_input(general_dict)
    if not is_success:
        return {}, "Failed: Lack of %s" % lack_fields

    # check other_dict, reduce the complicated attr
    for attr in ["umu", "phi"]:
        if attr in other_dict:
            other_dict.pop(attr)
    if ic_set:
        other_dict["ic_file"] = convert_cloud_to_file("ic_set", ic_set)
    elif ic_file:
        other_dict["ic_file"] = ic_file
    else:
        other_dict["ic_file"] = []
    if wc_set:
        other_dict["wc_file"] = convert_cloud_to_file("wc_set", wc_set)
    elif wc_file:
        other_dict["wc_file"] = wc_file
    else:
        other_dict["wc_file"] = []

    if source_type and source_file and source_unit:
        s_type = source_type[0].split(" ")[1]
        s_unit = source_unit[0].split(" ")[1]
        s_file = source_file[0].split(" ")[1]
        other_dict["source"] = ["source %s %s %s " % (s_type, s_file, s_unit)]

    process_special_general_dict(general_dict)

    process_zout_and_altitude(general_dict)
    logging.info(general_dict)
    phi_value = modify(general_dict["azimuth_angle"], {})
    logging.info(phi_value)

    #umu and distance
    umu_value, distance_value, old_umu_value, old_distance_value = get_umu_and_distance(general_dict)

    #type
    output_type = process_output_type(modify_attr_dict["output_quantity"], modify_attr_dict["output_process"])
    if output_type == 0:
        if modify_attr_dict["output_quantity"]:
            data.extend(modify_attr_dict["output_quantity"])
        if modify_attr_dict["output_process"]:
            data.extend(modify_attr_dict["output_process"])

    #create grid_file
    main_wave = main_wave[0].split(" ")[1]

    if main_wave == u"设置波长":
        modify_attr_dict["wavelength"] = change_um_to_nm("wavelength", modify_attr_dict["wavelength"])
        wave_grid_file = create_grid_file(modify_attr_dict["wavelength"])
        data.extend(wave_grid_file)

    if main_wave == u"设置波数":
        wave_grid_file = create_grid_file_by_count(modify_attr_dict["wavecount"]);
        data.extend(wave_grid_file)

    #modify
    value_list = modify_general(general_dict)
    for value in value_list:
        data.extend(value)

    # add other attrs
    for attr, value in other_dict.items():
        data.extend(value)


    #check atmosphere_file user_defined or choice
    modify_attr_dict["atmosphere_file"] = ["atmosphere_file %s" % get_atmos_file(atmos_file_list, atmosphere_define)]

    #form a conf_dict for cycle running uvspec
    res_dict = form_conf_dict(old_umu_value, old_distance_value, umu_value, phi_value, distance_value, modify_attr_dict["atmosphere_file"], output_type, data, general_dict["direction"])

    return res_dict, "Success!"

def getInputDict(Options):
    data=[]
    general_dict = {}
    modify_attr_dict = {"wavecount": [], "wavelength": [], "output_quantity": [], "output_process": []}
    atmos_list = ["gas_file", "pressure_file", "temperature_file", "latitude_file"]
    atmos_file_list = []
    omit_list = ["general_location", "main_wave"]
    other_dict = {}
    phi_value = None
    atmosphere_define = ""
    ic_set = ""
    wc_set = ""
    ic_file = ""
    wc_file = ""

    source_type = ""
    source_file = ""
    source_unit = ""

    for option_name, Option_obj in Options.items():
        if Option_obj.IsChanged() and  Option_obj.IsSet():
            group = Option_obj.group if hasattr(Option_obj, "group") else ""
            value = Option_obj.GetWriteValue()
            if option_name in omit_list:
                # attr in omit tabs, shoule be deleted
                continue

            if group == "general":
                # new tab, should be specialy processed
                general_dict[option_name] = value
            elif option_name in modify_attr_dict:
                # attr in other tabs, shoule be redefined
                modify_attr_dict[option_name] = value
            elif option_name in atmos_list:
                atmos_file_list.append(value)
            elif option_name == "ic_set":
                ic_set = value
                continue
            elif option_name == "wc_set":
                wc_set = value
                continue
            elif option_name == "ic_file":
                ic_file = value
                continue
            elif option_name == "wc_file":
                wc_file = value
                continue
            elif option_name == "source_type":
                source_type = value
                continue
            elif option_name == "source_file":
                source_file = value
                continue
            elif option_name == "source_unit":
                source_unit = value
                continue
            elif option_name == "aerosol_haze":
                other_dict["aerosol_haze"] = change_aerosol_haze(value)
            elif option_name == "aerosol_season":
                other_dict["aerosol_season"] = change_aerosol_season(value)
            elif option_name == "aerosol_vulcan":
                other_dict["aerosol_vulcan"] = change_aerosol_vulcan(value)
            elif option_name == "atmosphere_define":
                atmosphere_define = value[0].split(" ")[1]
            else:
                # attr in other tabs, should not be changed
                other_dict[option_name] = value
    if len(atmos_file_list) < 4:
        return {}, "Failed: Lack of atmosphere_file"

    #check general_dict 
    is_success, lack_fields = check_input(general_dict)
    if not is_success:
        return {}, "Failed: Lack of %s" % lack_fields

    # check other_dict, reduce the complicated attr
    for attr in ["umu", "phi"]:
        if attr in other_dict:
            other_dict.pop(attr)
    if ic_set:
        other_dict["ic_file"] = convert_cloud_to_file("ic_set", ic_set)
    elif ic_file:
        other_dict["ic_file"] = ic_file
    else:
        other_dict["ic_file"] = [] 
    if wc_set:
        other_dict["wc_file"] = convert_cloud_to_file("wc_set", wc_set)
    elif wc_file:
        other_dict["wc_file"] = wc_file
    else:
        other_dict["wc_file"] = [] 

    if source_type and source_file and source_unit:
        s_type = source_type[0].split(" ")[1]
        s_unit = source_unit[0].split(" ")[1]
        s_file = source_file[0].split(" ")[1]
        other_dict["source"] = ["source %s %s %s " % (s_type, s_file, s_unit)]

    process_special_general_dict(general_dict)

    process_zout_and_altitude(general_dict)
    logging.info(general_dict)
    phi_value = modify(general_dict["azimuth_angle"], {})
    logging.info(phi_value)

    #umu and distance
    umu_value, distance_value, old_umu_value, old_distance_value = get_umu_and_distance(general_dict)

    #type
    output_type = process_output_type(modify_attr_dict["output_quantity"], modify_attr_dict["output_process"])
    if output_type == 0:
        if modify_attr_dict["output_quantity"]:
            data.extend(modify_attr_dict["output_quantity"])
        if modify_attr_dict["output_process"]:
            data.extend(modify_attr_dict["output_process"])

    #create grid_file
    if modify_attr_dict["wavelength"]:
        modify_attr_dict["wavelength"] = change_um_to_nm("wavelength", modify_attr_dict["wavelength"]) 
        wave_grid_file = create_grid_file(modify_attr_dict["wavelength"])
        data.extend(wave_grid_file)

    if modify_attr_dict["wavecount"]:
        wave_grid_file = create_grid_file_by_count(modify_attr_dict["wavecount"]);
        data.extend(wave_grid_file)

    #modify
    value_list = modify_general(general_dict)
    for value in value_list:
        data.extend(value)
    
    # add other attrs
    for attr, value in other_dict.items():
        data.extend(value)


    #check atmosphere_file user_defined or choice
    modify_attr_dict["atmosphere_file"] = ["atmosphere_file %s" % get_atmos_file(atmos_file_list, atmosphere_define)]

    #form a conf_dict for cycle running uvspec
    res_dict = form_conf_dict(old_umu_value, old_distance_value, umu_value, phi_value, distance_value, modify_attr_dict["atmosphere_file"], output_type, data, general_dict["direction"])

    return res_dict, "Success!"

def get_atmos_file(atmos_file_list, atmosphere_define):
    res_path = ""
    if atmosphere_define:
        res_path = check_atmosphere_file(atmosphere_define)
    else: 
        for file_value in atmos_file_list:
            select_key, select_val = file_value[0].split(" ")
            res_path = check_atmosphere_file_new(select_val, select_key)


    with open(res_path, "r") as fp:
        line_list = fp.readlines()
        data_list = [line.split() for index, line in enumerate(line_list)]
    for index, data in enumerate(data_list):
        if not data[0].startswith("#"):
            data[3] = str(float(data[1]) / float(data[2]) * (10 ** 19) / 1.3806645)
    res_list = ["    ".join(data) for data in data_list]
    with open(res_path, "w") as fp:
        fp.write("\n".join(res_list))
    return res_path

def check_atmosphere_file_new(atmos_value, attr):
    if not atmos_value:
        return ""
    #get file path
    atmos_dict = {
                     "midlatitude_summer": "./atmmod/afglms.dat",
                     "subarctic_summer": "./atmmod/afglss.dat",
                     "midlatitude_winter": "./atmmod/afglmw.dat",
		     "subarctic_winter": "./atmmod/afglsw.dat",
		     "us-standard": "./atmmod/afglus.dat",
		     "tropics": "./atmmod/afglt.dat",
                 }
    file_path = atmos_dict.get(atmos_value, "")
    tgt_dir = os.path.dirname(file_path)
    if not file_path:
        return ""
    res_path = os.path.join(tgt_dir, "tmp.data")
    if not os.path.exists(res_path):
        shutil.copy(file_path, res_path)
    with open(res_path, "r") as fp:
        line_list = fp.readlines()
        data_list = [line.split() for index, line in enumerate(line_list)]
        
    with open(file_path,  "r") as fp:
        line_list = fp.readlines()
        src_list = [line.split() for index, line in enumerate(line_list)]
    for index, data in enumerate(data_list):
        if src_list[index][0].startswith("#"):
            data = src_list[index]
        elif attr == "gas_file":
            data[3] = src_list[index][3]
            data[4] = src_list[index][4]
            data[5] = src_list[index][5]
            data[7] = src_list[index][7]
            data[8] = src_list[index][8]
        elif attr == "pressure_file":
            data[1] = src_list[index][1]
        elif attr == "temperature_file":
            data[2] = src_list[index][2]
        elif attr == "latitude_file":
            data[6] = src_list[index][6]

    res_list = ["    ".join(data) for data in data_list]
    with open(res_path, "w") as fp:
        fp.write("\n".join(res_list))
    return res_path


def check_atmosphere_file(atmos_define):
    if not atmos_define:
        return ""
    #get file path
    file_path = atmos_define
    res_path = os.path.join("./atmmod", "tmp.data")
    if file_path.endswith("csv"):
        use_obj = UserdDefine(file_path)
        use_obj.create_atmos_file(res_path)
    else:
        shutil.copy(file_path, res_path)
    return res_path


def check_input(general_dict):
    if "global_mode" in general_dict:
        general_dict.pop("global_mode")

    used_key = ["direction", "angle_of_pitch", "azimuth_angle", "distance"]
    for check_key in used_key:
        if check_key not in general_dict:
            return False, check_key
    return True, None
    

def process_output_type(output_quantity, output_process):
    quantity = output_quantity[0].split(' ')[1] if output_quantity else ""
    process = output_process[0].split(' ')[1] if output_process else ""
    if quantity != 'radiance&transmittance' and process != "spectral&integrate":
        rec_type = 0
    elif quantity == 'radiance&transmittance' and process == 'spectral&integrate':
        rec_type = 1
    elif quantity == 'radiance&transmittance':
        rec_type = 2
    elif process == 'spectral&integrate':
        rec_type = 3
    return rec_type

def form_conf_dict(old_umu_value, old_distance_value, umu_value, phi_value, distance_value, atmosphere_file, output_type, data, direction):
    res_dict = {}
    dir_des = direction[0].split(' ')[1]
    if phi_value is not None:
        res_dict["phi_value"] = phi_value[0].split(' ')[1:]
    for idx_x, umu in enumerate(umu_value):
        umu_key = old_umu_value[idx_x]
        for idx_y, altitude in enumerate(distance_value[idx_x]):
            distance_key = old_distance_value[idx_y]
            if dir_des == u"观测天空方向":
                atmos_file = create_new_file(atmosphere_file, altitude)
            else:
                atmos_file = atmosphere_file[0] 
            

            other_data = copy.deepcopy(data)
            type_data = copy.deepcopy(data)

            if dir_des == u"观测地球方向":
                type_data.extend(["altitude %s" % altitude])
                other_data.extend(["altitude %s" % altitude])

            other_data.extend([atmos_file, "umu %s" % umu])
            key = "%s_%s_radiance_spectral" % (umu_key, distance_key)
            res_dict[key] = other_data

            
            if output_type == 0:
                pass
            elif output_type == 1:
                type_data_1 = copy.deepcopy(type_data)
                type_data_1.extend([atmos_file, "umu %s" % umu, "output_quantity transmittance"])
                key = "%s_%s_%s_%s" % (umu_key, distance_key, "transmittance", "spectral")
                res_dict[key] = type_data_1

                type_data_2 = copy.deepcopy(type_data)
                type_data_2.extend([atmos_file, "umu %s" % umu, "output_process integrate"])
                key = "%s_%s_%s_%s" % (umu_key, distance_key, "radiance", "integrate")
                res_dict[key] = type_data_2


                type_data.extend([atmos_file, "umu %s" % umu,  "output_quantity transmittance", "output_process integrate"])
                key = "%s_%s_%s_%s" % (umu_key, distance_key, "transmittance", "integrate")
                res_dict[key] = type_data
            elif output_type == 2:
                type_data.extend([atmos_file, "umu %s" % umu, "output_quantity transmittance"])
                key = "%s_%s_%s_spectral" % (umu_key, distance_key, "transmittance")
                res_dict[key] = type_data
            elif output_type == 3:
                type_data.extend([atmos_file, "umu %s" % umu, "output_process integrate"])
                key = "%s_%s_radiance_%s" % (umu_key, distance_key, "integrate")
                res_dict[key] = type_data
 
    if not res_dict:
        res_dict["main"] = data
    return res_dict


def cal_liner_value(start_line_list, end_line_list, val):
    all_step = float(end_line_list[0]) - float(start_line_list[0])
    val_step = float(val) - float(start_line_list[0])
    new_list = []
    for index, start_val in enumerate(start_line_list):
        end_val = end_line_list[index]
        if index == 0:
            new_list.append(str(val))
        else:
            all_val = float(end_val) - float(start_val)
            new_list.append(str(all_val / all_step * val_step + float(start_val)))
    return new_list
    

def create_new_file(atmos_value, altitude):
    if not atmos_value:
        return []
    #dir_des = direction[0].split(' ')[1]
    
    #get file path
    atmos_key, file_path = atmos_value[0].split(" ")
    dirname = os.path.dirname(file_path)
    filename = os.path.basename(file_path)
    dir_path = os.path.join(dirname, "tmp")
    new_file_path = os.path.join(dir_path, "%s-%s" % (filename, altitude))

    #get new data from resource file
    new_data = []
    last_line = []
    append_mark = False
    with open(file_path, "r") as fp:
        fp_data = fp.read()
        data_list = fp_data.strip().split("\n")
        for index, line_data in enumerate(data_list):
            line_list = line_data.strip().split() 
            z_height = line_list[0]
            if z_height.startswith("#"): 
                new_data.append(line_data)
            elif float(z_height) == float(altitude):
                #new_data.extend(data_list[index-1:])
                new_data.extend(data_list[index:])
                break
            elif float(z_height) < float(altitude):
                if not append_mark and last_line:
                    border_val = cal_liner_value(last_line, line_list, altitude)
                    new_data.extend([" ".join(border_val)])
                    append_mark = True
                else:
                    new_data.extend(data_list[index:])
                    break
            elif float(z_height) > float(altitude):
                last_line = line_list

    #write to new file
    with open(new_file_path, "w") as new_fp:
        new_data_str = "\n".join(new_data)
        new_fp.write(new_data_str)
    return "%s %s" % (atmos_key, new_file_path)
        

def modify_general(general_dict):
    new_value_list = []
    for general_key, general_value in general_dict.items():
        new_value = modify(general_value, general_dict)
        if new_value:
            new_value_list.append(new_value)
    return new_value_list

def get_umu_and_distance(general_dict):
    umu_value = modify(general_dict.get("angle_of_pitch", []), general_dict)
    distance_value = modify(general_dict.get("distance", []), general_dict, {"umu": umu_value})

    value_list = general_dict.get("angle_of_pitch", [])[0].split(" ")
    start, end, step = value_list[1:]
    old_umu_value = numpy.arange(float(start), float(end) + 0.1, float(step)).tolist()
    old_umu_list = [str(umu) for umu in old_umu_value]

    value_list = general_dict.get("distance", [])[0].split(" ")
    start, end, step = value_list[1:]
    old_distance_value = numpy.arange(float(start), float(end) + 0.1, float(step)).tolist()
    old_distance_list = [str(distance) for distance in old_distance_value]

    if "angle_of_pitch" in general_dict:
        general_dict.pop("angle_of_pitch")
    if "distance" in general_dict:
        general_dict.pop("distance")

    return umu_value, distance_value, old_umu_list, old_distance_list

def modify(value, general_dict, other_dict={}):
    if not value:
        return []
    value_list = value[0].split(" ")
    obj_name = value_list[0]
    if obj_name == "azimuth_angle":
        new_value_list = []
        start, end, step = value_list[1:]
        phi_value = numpy.arange(float(start), float(end) + 0.1, float(step)).tolist()
        phi_str_value = [str(phi) for phi in phi_value]
        new_value_str = "phi %s" % ' '.join(phi_str_value)
        new_value_list.append(new_value_str)
    elif obj_name == "angle_of_pitch":
        start, end, step = value_list[1:]
        umu_value = numpy.arange(float(start), float(end) + 0.1, float(step)).tolist()
        direction_val = general_dict.get("direction", [])
        up_or_down = direction_val[0].split(" ")[1] if direction_val else u"观测天空方向"
        if up_or_down == u"观测天空方向":
            new_value_list = [str(-math.cos(umu/180 * math.pi)) for umu in umu_value]
        else:
            new_value_list = [str(math.cos(umu/180 * math.pi)) for umu in umu_value]
    elif obj_name == "direction":
        new_value_list = []
    elif obj_name == "distance":
        new_value_list = []
        start, end, step = value_list[1:]
        dis_value = numpy.arange(float(start), float(end) + 0.1, float(step)).tolist()

        umu_value_list = other_dict.get("umu", [])
        for umu in umu_value_list:
            altitude_cos = [float(distance) for distance in dis_value]
            new_value_list.append(altitude_cos)
    else:
        new_value_list = value
    return new_value_list
