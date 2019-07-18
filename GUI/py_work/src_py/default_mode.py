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

	group_name = 'DefaultMode'

	def __init__(self):
		documentation = get_spectral_documentation()

		default_route_type = option(	#TODO: undefined number of optional arguments are allowed
			name=u'路径类型',
			group='defalut_mode',
			helpstr=u'选择需要的路径类型',
			documentation=documentation['wavelength'],
			gui_inputs=(ListInput(name='Input.dft_mode.mixture_name', valid_range=[u"斜程路径", u"临边路径"], optional=True),),
			tokens= [ addToken(name='Input.aer.mixture_name', datatype=str, valid_range = ['continental_clean', 'continental_average', 'continental_polluted', 
						'urban', 'maritime_clean', 'maritime_polluted', 'maritime_tropical', 'desert', 'antarctic','desert_spheriods'] )], 
				#addSetting(name='Input.aer.n_species', setting=1, default='NOT_DEFINED_INTEGER'),],
				#addSetting(name='Input.aer.spec', setting=1) ],
			parents=['uvspec'], 
		)

		wavelength = option(
			name='wavelength',
			group='spectral',
			helpstr='Set the wavelength range by specifying first and last wavelength in nm.',
			documentation=documentation['wavelength'],
			gui_inputs=(FloatInput(name='Input.wl.start', default=None, valid_range=[0, 1000000.0]),
				    FloatInput(name='Input.wl.end', default=None, valid_range=[0, 1000000.0], optional=True),),
			tokens = [ addToken(name='Input.wl.start', datatype=float, default='NOT_DEFINED_FLOAT', valid_range=[0,1e6]),
				addToken(name='Input.wl.end', datatype=float, default='NOT_DEFINED_FLOAT', valid_range=[0,1e6], optional=True) ], #TODO:argument 2 should be bigger that argument 1
			parents=['uvspec'],
			non_parents=['wavelength_index'],
		)

		default_atmosphere_mode = option(	#TODO: undefined number of optional arguments are allowed
			name=u'大气模式',
			group='defalut_mode',
			helpstr=u'选择对应的大气模式',
			documentation=documentation['wavelength'],
			gui_inputs=(ListInput(name='Input.aer.mixture_name', valid_range=[u"中维度夏天", u"中维度冬天", u"高纬度夏天",
                        u"高纬度冬天", u"热带", u"标准美国大气廓线"], optional=True),),
			tokens= [ addToken(name='Input.aer.mixture_name', datatype=str, valid_range = ['continental_clean', 'continental_average', 'continental_polluted', 'urban', 'maritime_clean', 'maritime_polluted'] ), 
				addSetting(name='Input.aer.n_species', setting=-1, default='NOT_DEFINED_INTEGER'),
				addSetting(name='Input.aer.spec', setting=1) ],
			parents=['uvspec'], 
		)
		default_aerosol_mode = option(	#TODO: undefined number of optional arguments are allowed
			name=u'气溶胶类型',
			group='defalut_mode',
			helpstr='选择对应的气溶胶类型',
			documentation=documentation['wavelength'],
			gui_inputs=(ListInput(name='Input.aer.mixture_name', valid_range=[u"城市（干净）", u"城市（一般）", u"城市（污染）",
                        u"海洋（干净）", u"海洋（一般）", u"海洋（污染）", u"大陆", u"沙漠", u"南极"], optional=True),),
			#tokens= [ addToken(name='Input.aer.mixture_name', datatype=str, valid_range = ['continental_clean', 'continental_average', 'continental_polluted', 'urban', 'maritime_clean', 'maritime_polluted'] ), 
				#addSetting(name='Input.aer.n_species', setting=-1, default='NOT_DEFINED_INTEGER'),
				#addSetting(name='Input.aer.spec', setting=1) ],
			parents=['uvspec'], 
		)
		atmosphere_file = option(
			name='test_for_ywc',
			group='DefaultMode',
			helpstr='Location of the atmosphere data file.', 
			documentation=documentation['wavelength'], 
			tokens= addToken(name='Input.atmosphere_filename', datatype=str, valid_range=['subarctic_winter', 'subarctic_summer', 'midlatitude_summer', 'midlatitude_winter', 'tropics', 'US-standard', file]),
			parents=['uvspec'], 
			plot = {'plot_type': '2D',
				'optional_args': {'column_names': (
						"altitude",
						"pressure",
						"temperature",
						"air",
						"ozone",
						"oxygen",
						"water vapour",
						"CO2",
						"NO2",)
						  }
				},
			mandatory=True,
		)
		default_surface_visibility = option(
			name=u'地表能见度(Km)',
			group='DefaultMode', 
			helpstr=u'设置当前的地表能见距离',
			documentation=documentation['wavelength'], 
			gui_inputs=(FloatInput(name='Input.pressure', default='NOT_DEFINED_FLOAT', valid_range=[0, 1000.0]),),
			tokens=addToken(name='Input.pressure', datatype=float, default='NOT_DEFINED_FLOAT', valid_range=[0,1e3]),
			parents=['uvspec'],
		)
		default_surface_wind_speed = option(
			name=u'当前地表风速(m/s)',
			group='DefaultMode', 
			helpstr=u'设置当前的地表风速',
			documentation=documentation['wavelength'], 
			gui_inputs=(FloatInput(name='Input.pressure', default='NOT_DEFINED_FLOAT', valid_range=[0, 1000.0]),),
			tokens=addToken(name='Input.pressure', datatype=float, default='NOT_DEFINED_FLOAT', valid_range=[0,1e3]),
			parents=['uvspec'],
		)
		default_height = option(
			name=u'海拔高度',
			group='DefaultMode', 
			helpstr=u'设置当前的海拔高度',
			documentation=documentation['wavelength'], 
			gui_inputs=(FloatInput(name='Input.pressure', default='NOT_DEFINED_FLOAT', valid_range=[0, 1000.0]),),
			tokens=addToken(name='Input.pressure', datatype=float, default='NOT_DEFINED_FLOAT', valid_range=[0,1e3]),
			parents=['uvspec'],
		)
		default_temperature = option(
			name=u'温度',
			group='DefaultMode', 
			helpstr=u'设置当前的温度',
			documentation=documentation['wavelength'], 
			gui_inputs=(FloatInput(name='Input.pressure', default='NOT_DEFINED_FLOAT', valid_range=[0, 1000.0]),),
			tokens=addToken(name='Input.pressure', datatype=float, default='NOT_DEFINED_FLOAT', valid_range=[0,1e3]),
			parents=['uvspec'],
		)
		default_surface_type = option(	#TODO: undefined number of optional arguments are allowed
			name=u'地表类型',
			group='defalut_mode',
			helpstr='选择对应的地表类型',
			documentation=documentation['wavelength'],
			gui_inputs=(ListInput(name='Input.aer.mixture_name', valid_range=[u"城市（干净）", u"城市（一般）", u"城市（污染）",
                        u"海洋（干净）", u"海洋（一般）", u"海洋（污染）", u"大陆", u"沙漠", u"南极"], optional=True),),
			#tokens= [ addToken(name='Input.aer.mixture_name', datatype=str, valid_range = ['continental_clean', 'continental_average', 'continental_polluted', 'urban', 'maritime_clean', 'maritime_polluted'] ), 
				#addSetting(name='Input.aer.n_species', setting=-1, default='NOT_DEFINED_INTEGER'),
				#addSetting(name='Input.aer.spec', setting=1) ],
			parents=['uvspec'], 
		)
		default_reflectivity = option(
			name=u'反射率',
			group='DefaultMode', 
			helpstr=u'设置当前的反射率',
			documentation=documentation['wavelength'], 
			gui_inputs=(FloatInput(name='Input.pressure', default='NOT_DEFINED_FLOAT', valid_range=[0, 1000.0]),),
			tokens=addToken(name='Input.pressure', datatype=float, default='NOT_DEFINED_FLOAT', valid_range=[0,1e3]),
			parents=['uvspec'],
		)
		default_sensor_para = option(	#TODO: valid_ranges for GUI!!
			name=u'传感器参数',
			group='DefaultMode', 
			helpstr=u'设置传感器当前的参数',
			documentation=documentation['wavelength'],
			tokens=[addToken( name='Input.aer.modify[id1][id2]', datatype=float, gui_name=u'经度' ),
			addToken( name='Input.aer.modify[id1][id2]', datatype=float, gui_name=u'纬度' ),
			addToken( name='Input.aer.modify[id1][id2]', datatype=float, gui_name=u'高度' ),
                        addSetting( name='Input.aer.spec', setting=1, default=0) ], 
			non_unique=False,
		)
		default_wind_mode = option(	#TODO: valid_ranges for GUI!!
			name=u'云模式',
			group='DefaultMode', 
			helpstr=u'云模式设置',
			documentation=documentation['wavelength'],
			tokens=[addLogical( name='id1', logicals=[u'无云',u'卷云', u'消卷云', u'高层云', u"积云", u"层积云", u"层云", u"乱层云"], setting='MODIFY_VAR_',gui_name=u'云模式' ),
                        addToken( name='Input.aer.modify[id1][id2]', datatype=float, gui_name=u'消光系数' ),
			addToken( name='Input.aer.modify[id1][id2]', datatype=float, gui_name=u'有效尺度' ),
			addToken( name='Input.aer.modify[id1][id2]', datatype=float, gui_name=u'云厚度' ),
			addToken( name='Input.aer.modify[id1][id2]', datatype=float, gui_name=u'云层高度' ),
                        addSetting( name='Input.aer.spec', setting=1, default=0) ], 
			non_unique=False,
		)

		self.options = [default_route_type, default_atmosphere_mode, default_aerosol_mode, default_surface_visibility, default_surface_wind_speed, default_height, default_temperature,  default_surface_type, default_reflectivity, default_sensor_para, default_wind_mode]

	def __iter__(self):
		return iter(self.options)

def get_spectral_documentation():
	return {
		'mc_sun_angular_size' : r'''
	At the moment only useful together with \code{mc_panorama_view}.
	Set the angular radius of the sun in degrees. If omitted the radius is calculated 
	(more or less correctly) via the earth-sun distance (not well tested).
	If no \code{mc_backward_sun_shape_file} is given a spectral sun shape according to
	Koepke2001 is used.
		''',

		'mc_lidar' : r'''
	Use local estimator to simulate a lidar. If \code{mc_lidar} is set,
	you need to provide a lidar file for \code{mc_lidar_file}. A detailed
	documentation is available on request from Robert Buras.
		''',

		'mc_lidar_file' : r'''
	File containing positions, looking directions, and opening angles of 
	lasers and detectors for lidar simulations in MYSTIC.  Only meaningful 
	with \code{mc_lidar}. 
	\fcode{ 
	mc_lidar_file file 
	}
		''',

		'mc_radar' : r'''
	Switch on radar, works exactly like lidar, so use with \code{mc_lidar_file}.
        Use \code{mc_ris} to get good statistics. Has not been tested with \code{mc_vroom},
        it's recommended to switch that off. Use with \code{write_output_as_netcdf} to get
        additional reflectivity factor output in a mmclx-file (netcdf format).
		''',

		'source' : r'''
	Set the radiation source type
	\fcode{
	source  type 
	}
	where \code{type} is either \code{solar} or \code{thermal}.
	Solar radiation is per default output in W/(m2 nm) if no \code{mol\_abs\_param} is specified 
        or \code{mol\_abs\_param} options \code{crs}, \code{lowtran}, or \code{reptran} are specified.
        For all other \code{mol\_abs\_param} options
	the output is integrated over the wavelength band.
	Thermal radiation is per default output in W/(m2 cm-1), if REPTRAN is used or the bandwidth 
	is equal to 1 cm-1 (default for \code{mol\_abs\_param lowtran}). 
	Otherwise the output is the integrated flux over the
	wavenumber interval specified by \code{thermal\_bandwidth}, \code{thermal\_bands\_file},
	or by the \code{mol\_abs\_param} option (\code{kato}, \code{kato2}, \code{kato2.96}, 
	\code{fu}, or \code{avhrr\_kratz}).
	\fcode{
	source type [file] [unit]
	}
	The second argument \code{file} specifies the location of file holding the extraterrestrial spectrum.
        In general, \code{file} is required for solar calculations if \code{mol\_abs\_param} is not used.
	\code{file} is ignored if \code{mol\_abs\_param} other than \code{lowtran} oder \code{reptran} is specified.

	The file must contain two columns. Column 1 is the wavelength in nm, and column 2 
	the corresponding extraterrestrial flux. The user may freely use any units
	he/she wants for the extraterrestrial flux. The wavelength  specified grid
	defines the wavelength resolution at which results are returned. However, 
	the wavelength range is determined by \code{wavelength}. \code{file} may be 
	omitted for thermal radiation calculations (\code{source thermal}) as well as 
	\code{output_quantity transmittance} and \code{output_quantity reflectivity} calculations. If omitted, the 
	output resolution equals the internal wavelength grid which the model chooses 
	for the radiative transfer calculation.
	Comments start with \code{\#}. Empty lines are ignored.

	For some purposes it is useful to tell libRadtran the units of the spectrum.
	This can be done with the optional third argument. 
	Possible choises for \code{unit} are \code{per\_nm}, \code{per\_cm-1} or \code{per\_band}.
	If \code{unit} is set to \code{per\_nm}
	libRadtran assumes that the unit of the spectrum is W/(m2 nm), if set to \code{per\_cm-1}
	it assumes W/(m2 cm-1).

		''',
		'thermal_bandwidth' : r'''
	Specify a constant bandwidth in cm-1 for thermal calculations. 
	\fcode{
	thermal\_bandwidth value
	}
	The default is 1 cm-1.
	This option is ignored if used together with \code{mol\_abs\_param kato/kato2/kato2.96/fu/avhrr\_kratz}.
			''',				

		'thermal_bands_file' : r'''
	File with the center wavelengths and the wavelength band intervals to be used for 
	calculations in the thermal range. 
	\fcode{
	thermal\_bands\_file file
	}
	The following three columns are expected:
	center (or reference) wavelength, lower wavelength limit, upper wavelength limit [nm].
	\code{thermal\_bands\_file} defines the wavelength grid for the radiative transfer 
	calculation. The RTE solver is called for each of the wavelengths in the first column. 
	The atmospheric (scattering, absorption, etc) properties are also evaluated at these 
	wavelengths. For thermal radiation calculations, the Planck function is integrated 
	over the wavelength bands defined in the second and third columns. The result will
	therefore be a band-integrated irradiance which does only make sense when the 
	\code{source solar file} grid equals the \code{thermal\_bands\_file} grid.
				''',

		'wavelength_grid_file' : r'''
	Location of single column file that sets the wavelength grid used for the 
	internal transmittance calculations. 
	\fcode{
	wavelength\_grid\_file file
	}
	The wavelengths must be in nm.
	Do not use this option unless you know what you are doing.
	Comments start with \code{\#}. Empty lines are ignored.
				''',

		'wavelength' : r'''
	Set the wavelength range by specifying first and last wavelength in nm. 
	\fcode{
	wavelength lambda\_0 lambda\_1
	}
	The default output wavelength grid is that defined in \code{source solar file}, 
	unless \code{spline} is specified. Note that the radiative transfer calculations 
	are done on an internal grid which can be influenced with \code{wavelength\_grid\_file}
	or \code{mol\_tau\_file abs file}
				''',

		'wavelength_index' : r'''
	Set the wavelengths to be selected. To be used together with predefined wavelength grids,
	such as \code{wavelength\_grid\_file}, \code{mol\_tau\_file abs file} and particularly 
	useful in combination with the \code{mol\_abs\_param} option where often only a 
	specified number of wavelength bands is required. E.g., in combination with
	\code{mol\_abs\_param AVHRR\_KRATZ}, \code{wavelength\_index 15 15} will select wavelength
	index 15 which corresponds to channel 4, or \code{wavelength\_index 10 14} will select 
	those bands required for channel 3. Indices start from 1.
				''',
		}
