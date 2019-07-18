#coding: utf-8

"""--------------------------------------------------------------------
 * $Id: spectral_options.py 3145 2015-08-04 13:35:30Z josef.gasteiger $
 * 
 * This file is part of libRadtran.
 * Copyright (c) 1997-2012 by Arve Kylling, Bernhard Mayer,
 *                            Claudia Emde, Robert Buras
 *
 * ######### Contact info: http://www.libradtran.org #########
 *
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License   
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.        
 * 
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of  
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the   
 * GNU General Public License for more details.                    
 * 
 * You should have received a copy of the GNU General Public License          
 * along with this program; if not, write to the Free Software                
 * Foundation, Inc., 59 Temple Place - Suite 330, 
 * Boston, MA 02111-1307, USA.
 *--------------------------------------------------------------------"""

from option_definition import *

class setup_spectral_group():

	group_name = u'主页'
        def wavecount_func(self, *value_list):
            ret_list = []
            for index, value in enumerate(value_list):
                if index == 2:
                    continue
                src_value = float(value)
                if src_value:
                    ret_list.append(str(10000.0 / src_value))  
                else:
                    ret_list.append("0")  
            return ret_list

        def mode_func(self, *value_list):
            ret_list = []
            for index, value in enumerate(value_list):
                if index == 2:
                    continue
                src_value = float(value)
                if src_value:
                    ret_list.append(str(10000.0 / src_value))  
                else:
                    ret_list.append("0")  
            return ret_list
            
        def wavelength_func(self, *value_list):
            #print "input: %s" % value_list
            ret_list = []
	    for index, value in enumerate(value_list):
                if index == 2:
                    continue
                src_value = float(value)
                if src_value:
                    ret_list.append(str(10000.0 / src_value))  
                else:
                    ret_list.append("0")  
            return ret_list

	def __init__(self):
		documentation = get_spectral_documentation()
	        mode_information = option(
                        name = "mode_information",
			gui_name=u'模式设置:',
			group='general',
			helpstr=u'设置相应的模式',
			documentation=documentation.get('location', ''),
			gui_inputs=(InfoInput(name='name', default=None, optional=False),),
		)
		global_mode = option(
			name='global_mode',
			gui_name='          运行模式',
			group='general',
			helpstr=u'用户可根据需要选择是否启用自定义模式',
			documentation=documentation.get('direction', ''),
			gui_inputs=(ListInput(name='global_mode', valid_range=[u'单点模式', u'批处理模式'], optional=False),),
			parents=['uvspec'],
			childs=['multi_choice', 'direction', 'wavelength_step', 'general_time', 'general_location'],
			continious_update=True,
		)
		direction = option(
                        name = "direction",
			gui_name='          观测模式',
			group='general',
			helpstr=u'设置观测方向',
			documentation=documentation.get('direction', ''),
			gui_inputs=(ListInput(name='Input.ger.direction', valid_range=[u'观测天空方向', u"观测地球方向"], optional=False),),
		)
	        source_information = option(
                        name = "source_information",
			gui_name=u'辐射设置:',
			group='spectral',
			helpstr=u'设置相应的辐射模式',
			documentation=documentation.get('location', ''),
			gui_inputs=(InfoInput(name='name', default=None, optional=False),),
		)
		source_type = option(
			name='source_type',
			gui_name=u'          辐射源',
			group='spectral',
			helpstr=u'辐射源设置', 
			gui_inputs=(ListInput(name=u'辐射源', valid_range=['thermal', 'solar'], optional=False),),
			tokens= [addLogical(name='Input.source', logicals=['thermal', 'solar'], setting='SRC_'),
				 addToken(name='Input.filename[FN_EXTRATERRESTRIAL]', datatype=file, optional=True),
				 addLogical(name='Input.spectrum_unit', logicals=['per_nm', 'per_cm-1', 'per_band'], setting='UNIT_', optional=True ) ], 
			parents=['uvspec'], 
		)
		source_file = option(
			name='source_file',
			gui_name=u'          文件路径',
			group='spectral',
			helpstr=u'辐射源设置', 
			#documentation=documentation['source'], 
			gui_inputs=(FileInput(name=u'文件名称', optional=False),),
			tokens= [addLogical(name='Input.source', logicals=['thermal', 'solar'], setting='SRC_'),
				 addToken(name='Input.filename[FN_EXTRATERRESTRIAL]', datatype=file, optional=True),
				 addLogical(name='Input.spectrum_unit', logicals=['per_nm', 'per_cm-1', 'per_band'], setting='UNIT_', optional=True ) ], 
			parents=['uvspec'], 
		)
		source_unit = option(
			name='source_unit',
			gui_name=u'          单位设置',
			group='spectral',
			helpstr=u'辐射源设置', 
			#documentation=documentation['source'], 
			gui_inputs=(ListInput(name=u'单位', valid_range=['per_nm', 'per_cm-1', 'per_band'], optional=False),),
			tokens= [addLogical(name='Input.source', logicals=['thermal', 'solar'], setting='SRC_'),
				 addToken(name='Input.filename[FN_EXTRATERRESTRIAL]', datatype=file, optional=True),
				 addLogical(name='Input.spectrum_unit', logicals=['per_nm', 'per_cm-1', 'per_band'], setting='UNIT_', optional=True ) ], 
			parents=['uvspec'], 
		)
		spectral_information = option(
                        name = "spectral_information",
			gui_name=u'光谱设置:',
			group='spectral',
			helpstr=u'设置地理位置',
			documentation=documentation.get('location', ''),
			gui_inputs=(InfoInput(name='name', default=None, optional=False),),
		)
		main_wave = option(
			name='main_wave',
			gui_name='          变化设置',
			group='general',
			helpstr=u'用户选择设置光谱的方式',
			documentation=documentation.get('direction', ''),
			gui_inputs=(ListInput(name='global_mode', valid_range=[u'设置波长', u'设置波数'], optional=False),),
			parents=['uvspec'],
			childs=['wavelength', 'wavecount'],
			continious_update=True,
		)
		gene_wavelength = option(
                        name = "wavelength",
			gui_name=u'          波长范围',
			group='spectral',
			helpstr=u'设置光谱范围',
			#documentation=documentation['wavelength'],
			gui_inputs=(FloatInput(name=u'起始(um)', default=None, valid_range=[0, 10000000.0]),
				    FloatInput(name=u'终止(um)', default=None, valid_range=[0, 10000000.0], optional=True),
				    FloatInput(name=u'步长(um)', default=None, valid_range=[0, 10000000.0], optional=True)),
                        speaker='main_wave',
			enable_values=(u"设置波长",),
			#parents=['wavecount'],
                        childs=['wavecount'],
                        change_speaker='wavecount',
                        change_values=self.wavelength_func,
		)
		gene_wavecount = option(
                        name = "wavecount",
			gui_name=u'          波数范围',
			group='spectral',
			helpstr=u'设置波数范围',
			#documentation=documentation['wavelength'],
			gui_inputs=(FloatInput(name=u'起始(cm-1)', default=None, valid_range=[0, 10000000000.0]),
				    FloatInput(name=u'终止(cm-1)', default=None, valid_range=[0, 10000000000.0], optional=True),
				    FloatInput(name=u'步长(cm-1)', default=None, valid_range=[0, 10000000000.0], optional=True)),
			#parents=['wavelength'],
                        speaker='main_wave',
			enable_values=(u"设置波数",),
                        childs=['wavelength'],
                        change_speaker='wavelength',
                        change_values=self.wavecount_func,
		)
		sight_information = option(
                        name = "sight_information",
			gui_name=u'观测几何:',
			group='general',
			helpstr=u'设置地理位置',
			documentation=documentation.get('location', ''),
			gui_inputs=(InfoInput(name='name', default=None, optional=False),),
		)
		general_location = option(
                        name = "general_location",
			gui_name='          经纬度',
			group='general',
			helpstr=u'设置地理位置',
			documentation=documentation.get('location', ''),
			gui_inputs=(FloatInput(name=u'经度(deg)', default=None, valid_range=[0, 180.0]),
				    FloatInput(name=u'纬度(deg)', default=None, valid_range=[0, 180.0], optional=True),),
		)
		sight_height = option(
                        name = "zout",
			gui_name='          视点高度',
			group='general',
			helpstr=u'设置地理位置',
			documentation=documentation.get('location', ''),
			gui_inputs=(FloatInput(name=u'高度(km)', default=None, valid_range=[0, 100000.0]),),
		)
		multi_choice = option(
                        name = "multi_choice",
			gui_name='          批处理设置',
			group='general',
			helpstr=u'设置观测方向',
			documentation=documentation.get('direction', ''),
			gui_inputs=(ListInput(name='Input.ger.direction', valid_range=[u'观测方位角', u"观测俯仰角", u"距离"], optional=False),),
			parents=['global_mode'],
			childs=['azimuth_angle', 'angle_of_pitch', 'distance'],
			speaker='global_mode',
			enable_values=(u"批处理模式",)
		)
		azimuth_angle = option(
                        name = "azimuth_angle",
			gui_name='          观测方位角',
			group='general',
			helpstr=u'设置方位角',
			documentation=documentation.get('azimuth_angle',''),
			gui_inputs=(FloatInput(name=u'起始(deg)', default=None, valid_range=[0, 180.0]),
				    FloatInput(name=u'终止(deg)', default=None, valid_range=[0, 180.0], optional=True),
				    FloatInput(name=u'步长(deg)', default=None, valid_range=[0, 180.0], optional=True),),

			parents=['multi_choice'],
                        speaker='multi_choice',
			enable_values=(u"观测方位角",)
		)
		angle_of_pitch = option(
                        name = "angle_of_pitch",
			gui_name='          观测俯仰角',
			group='general',
			helpstr=u'设置俯仰角',
			documentation=documentation.get('angle_of_pitch', ''),
			gui_inputs=(FloatInput(name=u'起始(deg)', default=None, valid_range=[0, 180]),
				    FloatInput(name=u'终止(deg)', default=None, valid_range=[0, 180], optional=True),
				    FloatInput(name=u'步长(deg)', default=None, valid_range=[0, 180], optional=True),),
			parents=['multi_choice'],
                        speaker='multi_choice',
			enable_values=(u"观测俯仰角",)
		)
		distance = option(
                        name = "distance",
			gui_name='          观测高度',
			group='general',
			helpstr=u'设置距离',
			documentation=documentation.get('distance', ''),
			gui_inputs=(FloatInput(name=u'起始(km)', default=None, valid_range=[0, 10000.0]),
				    FloatInput(name=u'终止(km)', default=None, valid_range=[0, 10000.0], optional=True),
				    FloatInput(name=u'步长(km)', default=None, valid_range=[0, 10000.0], optional=True),),
			parents=['multi_choice'],
                        speaker='multi_choice',
			enable_values=(u"距离",)
		)
	        sur_temperature = option(
	        	name='sur_temperature', 
			gui_name='         表面温度',
	        	group='surface',
	        	helpstr='Surface temperature.',
	        	#documentation=documentation['sur_temperature'], 
	        	gui_inputs=(FloatInput(name=u'表面温度'),),
	        )
	        albedo = option(
	        	name='albedo',
			gui_name='         反照率',
	        	group='surface',
	        	helpstr='Lambertian surface albedo',
	        	#documentation=documentation['albedo'], 
	        	gui_inputs=(FloatInput(name=u'反照率', default=0.0, valid_range=[0, 1]),),
	        )

		sza = option(
                        name = "sza",
			gui_name='         太阳俯仰角',
			group='surface',
			helpstr=u'设置时间',
			documentation=documentation.get('time', ''),
			gui_inputs=(FloatInput(name=u'(deg)', default=None, valid_range=[0, 180]),),
		)
		phi0 = option(
                        name = "phi0",
			#gui_name='',
			gui_name='         太阳方位角',
			group='surface',
			helpstr=u'设置时间',
			documentation=documentation.get('time', ''),
			gui_inputs=(FloatInput(name=u'(deg)', default=None, valid_range=[0, 180]),),
		)
                day_of_year = option(
                    name='day_of_year',
		    gui_name='          年中日',
                    group='general',
                    helpstr='Correction fo sun-earth distance',
		    gui_inputs=(IntegerInput(name=u'(1-366)', default=None, valid_range=[1, 366]),),
                    parents=['uvspec'], 
                )
		output_information = option(
                        name = "output_information",
			gui_name=u'输出设置:',
			group='output',
			helpstr=u'设置地理位置',
			documentation=documentation.get('location', ''),
			gui_inputs=(InfoInput(name='name', default=None, optional=False),),
		)
		output_process = option(
			name='output_process',
			gui_name=u'          输出处理',
			group='output',
			helpstr='Decide how the output from \code{uvspec} is processed.',
			#documentation=documentation['output_process'],
			gui_inputs=(ListInput(name='Input.output_unit_processing', valid_range=['integrate', 'sum', 'rgbnorm', 'rgb_norm', 'rgb', 'per_nm', 'per_cm-1', 'per_band', "spectral&integrate"], optional=False),),
			tokens=addToken(name='Input.output_unit_processing', datatype=str, valid_range=['integrate','sum','rgbnorm','rgb_norm','rgb',
										   'per_nm','per_cm-1','per_band'] ),
		)

		output_format = option(
			name='output_format', 
			gui_name=u'          输出格式',
			group='output',
			helpstr='Output format',
			#documentation=documentation['output_format'],
			tokens=addLogical(name='Input.output_format', logicals=['ascii','flexstor','netCDF','sat_picture'], setting='OUTPUT_FORMAT_'), 
		)

		output_user = not_yet_lex2py_option(
			name='output_user',
			gui_name=u'          输出自定义',
			group='output',
			helpstr='User defined output', 
			#documentation=documentation['output_user'],
			#gui_inputs=(TextInput(name=''),),
			gui_inputs=(ListInput(name='output_user', valid_range=['lambda uu', 'wavenumber uu'], optional=False),),
			tokens=addToken(name="", datatype=str),
			#parents=['uvspec'],
		)

		output_quantity = option(
			name='output_quantity',
			gui_name=u'          输出物理量',
			group='output',
			helpstr='Define output quantity to calculate instead of absolute quantities.',
			#documentation=documentation['output_quantity'],
			tokens=addLogical(name='Input.calibration', logicals=['reflectivity','transmittance','brightness', 'radiance&transmittance'], setting='OUTCAL_' ),
		)

		self.options = [mode_information, global_mode, direction,
                                source_information, source_type, source_unit, source_file,
                                spectral_information, main_wave, gene_wavelength, gene_wavecount,
                                output_information, output_process, output_format, output_user, output_quantity,
                                sight_information, general_location, sight_height, multi_choice, angle_of_pitch, azimuth_angle, distance, sur_temperature, albedo, sza, phi0, day_of_year]

	def __iter__(self):
		return iter(self.options)

def get_spectral_documentation():
	return {
		'direction' : u"设置为观测天空方向还是观测地球方向",

		}
