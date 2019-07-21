#coding: utf-8
# This Python file uses the following encoding: utf-8

import os
import sys
import logging


class QtConfManager(object):

    def __init__(self, filepath=""):
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
        with open("conf_temp.txt", 'r') as fp:
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
            input_key, input_val = line_data.split(' ')
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

        return True, self.out_file_path, out_dict

    def process_angle_of_pitch(self, qt_dict, out_dict):
        key = "angle_of_pitch"
        start = qt_dict.get("angle_of_pitch_start", '0')
        end = qt_dict.get("angle_of_pitch_end", '0')
        step = qt_dict.get("angle_of_pitch_step", '0')
        if step and step != '0':
            out_dict["multi_choice"] = [u"multi_choice 观察方位角"]
        out_dict[key] = ["{0} {1} {2} {3}".format(key, start, end, step)]

    def process_azimuth_angle(self, qt_dict, out_dict):
        key = "azimuth_angle"
        start = qt_dict.get("azimuth_angle_start", '0')
        end = qt_dict.get("azimuth_angle_end", '0')
        step = qt_dict.get("azimuth_angle_step", '0')
        if step and step != '0':
            out_dict["multi_choice"] = [u"multi_choice 观察俯仰角"]
        out_dict[key] = ["{0} {1} {2} {3}".format(key, start, end, step)]

    def process_distance(self, qt_dict, out_dict):
        key = "distance"
        start = qt_dict.get("distance_start", '0')
        end = qt_dict.get("distance_end", '0')
        step = qt_dict.get("distance_step", '0')
        if step and step != '0':
            out_dict["multi_choice"] = [u"multi_choice 距离"]
        out_dict[key] = ["{0} {1} {2} {3}".format(key, start, end, step)]

    def process_wavelength(self, qt_dict, out_dict):
        key = "wavelength"
        start = qt_dict.get("wavelength_start", '0')
        end = qt_dict.get("wavelength_end", '0')
        step = qt_dict.get("wavelength_step", '0')
        if step and step != '0':
            out_dict["main_wave"] = [u"main_wave 设置波长"]
        out_dict[key] = ["{0} {1} {2} {3}".format(key, start, end, step)]

    def process_wavecount(self, qt_dict, out_dict):
        key = "wavecount"
        start = qt_dict.get("wavecount_start", '0')
        end = qt_dict.get("wavecount_end", '0')
        step = qt_dict.get("wavecount_step", '0')
        if step and step != '0':
            out_dict["main_wave"] = [u"main_wave 设置波数"]
        out_dict[key] = ["{0} {1} {2} {3}".format(key, start, end, step)]

    def process_location(self, qt_dict, out_dict):
        pass

    def merge_input_fields(self, input_key, *input_list):
        ret_list = [input_key]
        for input_val in input_list:
            ret_list.append(input_val)
        return " ".join(ret_list)

def process_qt_input(filepath):
    qtManager = QtConfManager(filepath)
    is_success, out_path, response = qtManager.process_qt_input()
    return is_success, out_path, response

def run(in_path):
    log_path = "%s.stdout" % in_path
    is_success, out_path, out_dict = process_qt_input(in_path)
    if not is_success:
        return 201, u"预处理Qt文件失败！"

    from uvspec_run import OnRun
    #import py_work.uvspec_run
    is_success, data_list = OnRun(out_dict, out_path, log_path)

    if not is_success:
        return 202, u"运行失败！"

    return 200, u"运行成功"


if __name__ == "__main__":
    a=sys.argv[0]
    in_path = sys.argv[1]
    std_out_path = "%s.stdout" % in_path

    with open(std_out_path, "w") as fp:
        args_test = " ".join(sys.argv)
        fp.write(args_test)

    #os.chdir(os.path.dirname(a))
    status_cod, response = run(in_path)
    '''
    with open(std_out_path, "w") as fp:
        fp.write("finished")
    '''




