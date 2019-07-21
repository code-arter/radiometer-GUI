#coding: utf-8
# This Python file uses the following encoding: utf-8

import os
import sys
import traceback
#sys.path.append("py_work")
import logging

#import uuid


class QtConfManager(object):

    def __init__(self, filepath="", conf_path=""):
        self.conf_path = conf_path

        self.read_template()
        self.read_qt_out(filepath)

    def read_qt_out(self, filepath):
        if(not os.path.exists(filepath)):
            logging.error("input file not exists!")
            return False, {}
        self.path = filepath

    def read_template(self):
        self.key_conf = {}
        #return
        print os.getcwd()
        print sys.path[0]
        with open(self.conf_path, 'r') as fp:
            data = fp.read()
        self.key_conf = {}
        line_list = data.split('\n')
        for line_data in line_list:
            self.key_conf[line_data] = '1'

    def read_conf(self):
        qt_dict = {}
        with open(self.path, "r") as fp:
            data = fp.read()
        data_list = data.split('\n')
        print data_list

        for line_data in data_list:
            if(line_data.startswith('#')) or not line_data:
                continue
            input_key, input_val = line_data.split(' ', 1)
            if(input_key == "out_file_path"):
                self.out_file_path = input_val
            else:
                qt_dict[input_key] = input_val
        return qt_dict

    def get_out_path(self):
        return self.out_file_path


    def make_out_dict(self, qt_dict):
        out_dict = {}
        for qt_key, qt_val in qt_dict.items():
            if qt_key in self.key_conf:
                out_dict[qt_key] = ["%s %s" % (qt_key, qt_val.decode("utf-8"))]
        return out_dict

    def process_qt_input(self):

        qt_dict = self.read_conf()

        out_dict = self.make_out_dict(qt_dict)

        self.process_wavelength(qt_dict, out_dict)

        self.process_wavecount(qt_dict, out_dict)

        self.process_location(qt_dict, out_dict)

        self.process_angle_of_pitch(qt_dict, out_dict)

        self.process_azimuth_angle(qt_dict, out_dict)

        self.process_distance(qt_dict, out_dict)

        self.process_multi_val(qt_dict, out_dict)

        return True, self.out_file_path, out_dict

    def process_multi_val(self, qt_dict, out_dict):
        multi_setting = ["mixing_ratio", "mol_modify",
                         "aerosol_file", "aerosol_modify",
                         "wc_set", "wc_modify", "ic_set", "ic_modify", "ic_fu", "cloudcover"]
        for setting in multi_setting:
            if setting not in qt_dict:
                continue
            new_list = []
            for val in qt_dict[setting].split("; "):
                new_val = "%s %s" % (setting, val)
                new_list.append(new_val)
            out_dict[setting] = new_list

    def process_angle_of_pitch(self, qt_dict, out_dict):
        key = "angle_of_pitch"
        start = qt_dict.get("angle_of_pitch_start", '0')
        end = qt_dict.get("angle_of_pitch_end", '0')
        step = qt_dict.get("angle_of_pitch_step", '0')
        out_dict[key] = ["{0} {1} {2} {3}".format(key, start, end, step)]

    def process_azimuth_angle(self, qt_dict, out_dict):
        key = "azimuth_angle"
        start = qt_dict.get("azimuth_angle_start", '0')
        end = qt_dict.get("azimuth_angle_end", '0')
        step = qt_dict.get("azimuth_angle_step", '0')
        out_dict[key] = ["{0} {1} {2} {3}".format(key, start, end, step)]

    def process_distance(self, qt_dict, out_dict):
        key = "distance"
        start = qt_dict.get("distance_start", '0')
        end = qt_dict.get("distance_end", '0')
        step = qt_dict.get("distance_step", '0')
        out_dict[key] = ["{0} {1} {2} {3}".format(key, start, end, step)]

    def process_wavelength(self, qt_dict, out_dict):
        key = "wavelength"
        start = qt_dict.get("wavelength_start", '0')
        end = qt_dict.get("wavelength_end", '0')
        step = qt_dict.get("wavelength_step", '0')
        out_dict[key] = ["{0} {1} {2} {3}".format(key, start, end, step)]

    def process_wavecount(self, qt_dict, out_dict):
        key = "wavecount"
        start = qt_dict.get("wavecount_start", '0')
        end = qt_dict.get("wavecount_end", '0')
        step = qt_dict.get("wavecount_step", '0')
        out_dict[key] = ["{0} {1} {2} {3}".format(key, start, end, step)]

    def process_location(self, qt_dict, out_dict):
        pass

    def merge_input_fields(self, input_key, *input_list):
        ret_list = [input_key]
        for input_val in input_list:
            ret_list.append(input_val)
        return " ".join(ret_list)

def process_qt_input(filepath, conf_path):
    qtManager = QtConfManager(filepath, conf_path)
    is_success, out_path, response = qtManager.process_qt_input()
    return is_success, out_path, response

def run(in_path, script_path):
    try:
        log_path = "%s.stdout" % in_path
        with open(log_path, "w") as fp:
            fp.write("Now Start!!!\n")

        conf_path = os.path.join(os.path.dirname(script_path), "qt_conf", "conf_temp.txt")

        is_success, out_path, out_dict = process_qt_input(in_path, conf_path)
        if not is_success:
            return 201, u"预处理Qt文件失败！"
        dirname = os.path.join(os.path.dirname(script_path), "py_work")
        #sys.path.append("py_work")

        os.chdir(dirname)
        from py_work.uvspec_run import OnRun
        #import py_work.uvspec_run
        is_success, data_log = OnRun(out_dict, out_path, log_path)
        logging.info(data_log)
        #is_success = True
        if not is_success:
            return 202, u"运行失败！"

        return 200, u"运行成功"
    except Exception as e:
        logging.error(traceback.format_exc())



if __name__ == "__main__":
    a=sys.argv[0]
    in_path = sys.argv[1]
    std_out_path = "%s.stdout" % in_path

    with open(std_out_path, "w") as fp:
        args_test = " ".join(sys.argv)
        fp.write(args_test)

    #os.chdir(os.path.dirname(a))
    status_cod, response = run(in_path, "D:/project/qt/radiometer/build-GUI-Desktop_Qt_5_13_0_MinGW_64_bit-Debug/debug/process_qt_input.py")
    '''
    with open(std_out_path, "w") as fp:
        fp.write("finished")
    '''




