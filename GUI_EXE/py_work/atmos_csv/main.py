#coding: utf-8
import os
import csv
import time
from scipy import interpolate #导入内插方式 

class CsvFile(object):

    def __init__(self, csv_path):
        self.csv_dict = {}
        if not os.path.exists(csv_path):
            print "csv path not exists!!!"
            return
        with open(csv_path, 'r') as fp:
            data_list = csv.reader(fp)
            for data in data_list:
                index = data[0]
                code = data[2]
                if code == "400":
                    self.csv_dict["height"] = data[3:]
                elif index and code:
                    key = "%s-%s" % (index, code)
                    self.csv_dict[key] = data[3:]

    def get_specific_item(self, key, default_value=[]):
        return self.csv_dict.get(key, default_value)

class UserdDefine(object):
    key_dict = {
                "GPS": "13-31", 
                "SURFACE_DATA": "14-201", 
                "HEIGHT": "Record-400", 
                "TEMP_DATA": "15-401", 
                "STEAM_DATA": "16-402", 
                "LIQUID_DATA": "17-403", 
                "HUMI_DATA": "18-404"
               }

    SRC_FILE_DICT = {
                     "SUMMER-mid": "atmmod/afglms.dat",
                     "SUMMER-high": "atmmod/afglss.dat",
                     "WINTER-mid": "atmmod/afglmw.dat",
                     "WINTER-high": "atmmod/afglsw.dat"
                    }
    def __init__(self, csv_data, tgt_path=""):
        self.csv_data = CsvFile(csv_data)
        self.tgt_path = tgt_path

    def process_src_file(self, src_file):
        attr_dict = self.get_src_dict(src_file)
        func_dict = self.get_func_dict(attr_dict)
        return func_dict

    def get_src_dict(self, src_file):
        key_list = ["height", "pressure", "temperature", "air", "o3", "o2", "h2o", "co2", "no2"]
        attr_dict = {}
                     
        with open(src_file, "r") as fp:
            data = fp.readlines()
        for line in data:
            if line.startswith("#"):
                continue
            height, pressure, temp, air, o3, o2, h2o, co2, no2 = line.split()
            attr_list = line.split()
            for index, attr in enumerate(attr_list):
                if key_list[index] not in attr_dict:
                    attr_dict[key_list[index]] = [] 
                attr_dict[key_list[index]].append(float(attr))
        return attr_dict

    def get_func_dict(self, attr_dict):
        x_list = attr_dict["height"][::-1]
        res_dict = {}
        for key, y_list in attr_dict.items():
            key_dict = {}
            for kind in ["linear", "quadratic"]:
                f = interpolate.interp1d(x_list, y_list[::-1], kind=kind)
                key_dict[kind] = f
            res_dict[key] = key_dict
        return res_dict

    def create_atmos_file(self, tgt_path):
        season, time = self._get_csv_time()
        level, latitude = self._get_latitude()
        src_file = self.judge_src_file(season, level)
        fun_dict = self.process_src_file(src_file)
        tmp_list, steam_list, liquid_list, humi_list = self._get_regular_data()
        height_list = self._get_csv_height()
        total_list = self.create_total_list(fun_dict, height_list, tmp_list, steam_list)

        self._create_from_csv(total_list, src_file, tgt_path)
        

    def create_total_list(self, fun_dict, height_list, tmp_list, steam_list):
        method = "linear"
        total_list = []
        for index, height in enumerate(height_list):
            key_list = ["height", "pressure", "temperature", "air", "o3", "o2", "h2o", "co2", "no2"]
            height = float(height)
            sig_pressure = "%.5f" % (fun_dict["pressure"][method](height))
            sig_tmp = tmp_list[index]
            sig_air = "%.6e" % fun_dict["air"][method](height)
            sig_o3 = "%.6e" % fun_dict["o3"][method](height)
            sig_o2 = "%.6e" % fun_dict["o2"][method](height)
            #sig_h2o = fun_dict["h2o"][method](height)
            sig_h2o = "%.6e" % float(steam_list[index])
            sig_co2 = "%.6e" % fun_dict["co2"][method](height)
            sig_no2 = "%.6e" % fun_dict["no2"][method](height)

            sig_total = [sig_pressure, sig_tmp, sig_air, sig_o3, sig_o2, sig_h2o, sig_co2, sig_no2]
            sig_str_total = [format(str(ele), ">15") for ele in sig_total]
            sig_str_total.insert(0, format(str(height), ">5"))
            total_list.append("".join(sig_str_total))
        total_list = total_list[::-1]
        return total_list
            

    def _create_from_csv(self, total_list, src_file, tgt_path):
        with open(tgt_path, "w") as fp:
            total_str = "\n".join(total_list)
            fp.write(total_str)

    def _get_regular_data(self):
        res_list = []
        height_key = self.key_dict.get("HEIGHT", None)
        tmp_key = self.key_dict.get("TEMP_DATA", None)
        steam_key = self.key_dict.get("STEAM_DATA", None)
        liquid_key = self.key_dict.get("LIQUID_DATA", None)
        humi_key = self.key_dict.get("HUMI_DATA", None)
        for key in tmp_key, steam_key, liquid_key, humi_key:
            data = self._get_csv_data(key)
            res = data[1: -1]
            last = ['%.3f' % float(item) for item in res]
            res_list.append(last)
        return res_list

    def judge_src_file(self, season, level):
        key_str = "%s-%s" % (season, level)
        return self.SRC_FILE_DICT.get(key_str, "")

    def _get_gps_data(self):
        gps_key = self.key_dict.get("GPS", None)
        gps_data =self._get_csv_data(gps_key)
        return gps_data

    def _get_csv_data(self, key):
        if key is not None:
            csv_data = self.csv_data.get_specific_item(key)
        else:
            csv_data = []
        csv_data = [data for data in csv_data if data]
        return csv_data

    def _get_csv_time(self):
        gps_data = self._get_gps_data()
        now_time = gps_data[0] if gps_data else ""
        if now_time:
            time_turple = time.strptime(now_time, "%d/%m/%Y %H:%M:%S")
          
            tm_mon = time_turple.tm_mon
            if tm_mon >= 4 and tm_mon < 10:
                season = "SUMMER"
            else:
                season = "WINTER"
            return season, time
        else:
            return "", ""

    def _get_csv_height(self):
        src_list = self._get_csv_data("height")
        res_list = ["%.3f" % float(data) for data in src_list if self.is_float(data)]
        return res_list

    def _get_latitude(self):
        gps_data = self._get_gps_data()
        latitude = gps_data[1] if gps_data else ""
        latitude = float(latitude) * 0.01
        if latitude > 60:
            level = "high"
        elif latitude > 20:
            level = "mid"
        else:
            level = "low"
        return level, latitude

    def is_float(self, data):
        try:
            float(data)
            return True
        except Exception:
            return False
  

if __name__ == "__main__":
    tgt_path = "/tmp/test.data"
    use_obj = UserdDefine("./test.csv", tgt_path)
    use_obj.create_atmos_file(tgt_path)
