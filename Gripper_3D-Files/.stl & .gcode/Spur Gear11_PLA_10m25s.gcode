; HEADER_BLOCK_START
; BambuStudio 01.08.04.51
; model printing time: 4m 29s; total estimated time: 10m 25s
; total layer number: 25
; model label id: 72
; filament_density: 1.24,1.24
; filament_diameter: 1.75,1.75
; max_z_height: 10.00
; HEADER_BLOCK_END

; CONFIG_BLOCK_START
; accel_to_decel_enable = 0
; accel_to_decel_factor = 50%
; activate_air_filtration = 0,0
; additional_cooling_fan_speed = 70,70
; auxiliary_fan = 1
; bed_custom_model = 
; bed_custom_texture = 
; bed_exclude_area = 0x0,18x0,18x28,0x28
; before_layer_change_gcode = 
; best_object_pos = 0.5,0.5
; bottom_shell_layers = 3
; bottom_shell_thickness = 0
; bottom_surface_pattern = monotonic
; bridge_angle = 0
; bridge_flow = 1
; bridge_no_support = 0
; bridge_speed = 30
; brim_object_gap = 0.1
; brim_type = auto_brim
; brim_width = 5
; chamber_temperatures = 0,0
; change_filament_gcode = M620 S[next_extruder]A\nM204 S9000\n{if toolchange_count > 1 && (z_hop_types[current_extruder] == 0 || z_hop_types[current_extruder] == 3)}\nG17\nG2 Z{z_after_toolchange + 0.4} I0.86 J0.86 P1 F10000 ; spiral lift a little from second lift\n{endif}\nG1 Z{max_layer_z + 3.0} F1200\n\nG1 X70 F21000\nG1 Y245\nG1 Y265 F3000\nM400\nM106 P1 S0\nM106 P2 S0\n{if old_filament_temp > 142 && next_extruder < 255}\nM104 S[old_filament_temp]\n{endif}\nG1 X90 F3000\nG1 Y255 F4000\nG1 X100 F5000\nG1 X120 F15000\n\nG1 X20 Y50 F21000\nG1 Y-3\n{if toolchange_count == 2}\n; get travel path for change filament\nM620.1 X[travel_point_1_x] Y[travel_point_1_y] F21000 P0\nM620.1 X[travel_point_2_x] Y[travel_point_2_y] F21000 P1\nM620.1 X[travel_point_3_x] Y[travel_point_3_y] F21000 P2\n{endif}\nM620.1 E F[old_filament_e_feedrate] T{nozzle_temperature_range_high[previous_extruder]}\nT[next_extruder]\nM620.1 E F[new_filament_e_feedrate] T{nozzle_temperature_range_high[next_extruder]}\n\n{if next_extruder < 255}\nM400\n\nG92 E0\n{if flush_length_1 > 1}\n; FLUSH_START\n; always use highest temperature to flush\nM400\n{if filament_type[next_extruder] == "PETG"}\nM109 S220\n{else}\nM109 S[nozzle_temperature_range_high]\n{endif}\n{if flush_length_1 > 23.7}\nG1 E23.7 F{old_filament_e_feedrate} ; do not need pulsatile flushing for start part\nG1 E{(flush_length_1 - 23.7) * 0.02} F50\nG1 E{(flush_length_1 - 23.7) * 0.23} F{old_filament_e_feedrate}\nG1 E{(flush_length_1 - 23.7) * 0.02} F50\nG1 E{(flush_length_1 - 23.7) * 0.23} F{new_filament_e_feedrate}\nG1 E{(flush_length_1 - 23.7) * 0.02} F50\nG1 E{(flush_length_1 - 23.7) * 0.23} F{new_filament_e_feedrate}\nG1 E{(flush_length_1 - 23.7) * 0.02} F50\nG1 E{(flush_length_1 - 23.7) * 0.23} F{new_filament_e_feedrate}\n{else}\nG1 E{flush_length_1} F{old_filament_e_feedrate}\n{endif}\n; FLUSH_END\nG1 E-[old_retract_length_toolchange] F1800\n{if (flush_length_2 > 1) && (filament_type[next_extruder]=="PLA-CF" || filament_type[next_extruder]=="PETG")}\nM106 P1 S255\nM400 S3\nM106 P1 S0\nG1 X80 F15000\nG1 X60 F15000\nG1 X80 F15000\nG1 X60 F15000; shake to put down garbage\n\nG1 X70 F5000\nG1 X90 F3000\nG1 Y255 F4000\nG1 X100 F5000\nG1 Y265 F5000\nG1 X70 F10000\nG1 X100 F5000\nG1 X70 F10000\nG1 X100 F5000\nG1 X165 F15000; wipe and shake\nG1 Y245 F21000\nG1 X65 \nG1 Y265 F3000\n{endif}\nG1 E[old_retract_length_toolchange] F300\n{endif}\n\n{if flush_length_2 > 1}\n; FLUSH_START\nG1 E{flush_length_2 * 0.18} F{new_filament_e_feedrate}\nG1 E{flush_length_2 * 0.02} F50\nG1 E{flush_length_2 * 0.18} F{new_filament_e_feedrate}\nG1 E{flush_length_2 * 0.02} F50\nG1 E{flush_length_2 * 0.18} F{new_filament_e_feedrate}\nG1 E{flush_length_2 * 0.02} F50\nG1 E{flush_length_2 * 0.18} F{new_filament_e_feedrate}\nG1 E{flush_length_2 * 0.02} F50\nG1 E{flush_length_2 * 0.18} F{new_filament_e_feedrate}\nG1 E{flush_length_2 * 0.02} F50\n; FLUSH_END\nG1 E-[new_retract_length_toolchange] F1800\n{if (flush_length_3 > 1) && (filament_type[next_extruder]=="PLA-CF" || filament_type[next_extruder]=="PETG")}\nM106 P1 S255\nM400 S3\nM106 P1 S0\nG1 X80 F15000\nG1 X60 F15000\nG1 X80 F15000\nG1 X60 F15000; shake to put down garbage\n\nG1 X70 F5000\nG1 X90 F3000\nG1 Y255 F4000\nG1 X100 F5000\nG1 Y265 F5000\nG1 X70 F10000\nG1 X100 F5000\nG1 X70 F10000\nG1 X100 F5000\nG1 X165 F15000; wipe and shake\nG1 Y245 F21000\nG1 X65 \nG1 Y265 F3000\n{endif}\nG1 E[new_retract_length_toolchange] F300\n{endif}\n\n{if flush_length_3 > 1}\n; FLUSH_START\nG1 E{flush_length_3 * 0.18} F{new_filament_e_feedrate}\nG1 E{flush_length_3 * 0.02} F50\nG1 E{flush_length_3 * 0.18} F{new_filament_e_feedrate}\nG1 E{flush_length_3 * 0.02} F50\nG1 E{flush_length_3 * 0.18} F{new_filament_e_feedrate}\nG1 E{flush_length_3 * 0.02} F50\nG1 E{flush_length_3 * 0.18} F{new_filament_e_feedrate}\nG1 E{flush_length_3 * 0.02} F50\nG1 E{flush_length_3 * 0.18} F{new_filament_e_feedrate}\nG1 E{flush_length_3 * 0.02} F50\n; FLUSH_END\nG1 E-[new_retract_length_toolchange] F1800\n{if (flush_length_4 > 1) && (filament_type[next_extruder]=="PLA-CF" || filament_type[next_extruder]=="PETG")}\nM106 P1 S255\nM400 S3\nM106 P1 S0\nG1 X80 F15000\nG1 X60 F15000\nG1 X80 F15000\nG1 X60 F15000; shake to put down garbage\n\nG1 X70 F5000\nG1 X90 F3000\nG1 Y255 F4000\nG1 X100 F5000\nG1 Y265 F5000\nG1 X70 F10000\nG1 X100 F5000\nG1 X70 F10000\nG1 X100 F5000\nG1 X165 F15000; wipe and shake\nG1 Y245 F21000\nG1 X65 \nG1 Y265 F3000\n{endif}\nG1 E[new_retract_length_toolchange] F300\n{endif}\n\n{if flush_length_4 > 1}\n; FLUSH_START\nG1 E{flush_length_4 * 0.18} F{new_filament_e_feedrate}\nG1 E{flush_length_4 * 0.02} F50\nG1 E{flush_length_4 * 0.18} F{new_filament_e_feedrate}\nG1 E{flush_length_4 * 0.02} F50\nG1 E{flush_length_4 * 0.18} F{new_filament_e_feedrate}\nG1 E{flush_length_4 * 0.02} F50\nG1 E{flush_length_4 * 0.18} F{new_filament_e_feedrate}\nG1 E{flush_length_4 * 0.02} F50\nG1 E{flush_length_4 * 0.18} F{new_filament_e_feedrate}\nG1 E{flush_length_4 * 0.02} F50\n; FLUSH_END\n{endif}\n; FLUSH_START\nM400\nM109 S[new_filament_temp]\nG1 E2 F{new_filament_e_feedrate} ;Compensate for filament spillage during waiting temperature\n; FLUSH_END\nM400\nG92 E0\nG1 E-[new_retract_length_toolchange] F1800\nM106 P1 S255\nM400 S3\nG1 X80 F15000\nG1 X60 F15000\nG1 X80 F15000\nG1 X60 F15000; shake to put down garbage\n\nG1 X70 F5000\nG1 X90 F3000\nG1 Y255 F4000\nG1 X100 F5000\nG1 Y265 F5000\nG1 X70 F10000\nG1 X100 F5000\nG1 X70 F10000\nG1 X100 F5000\nG1 X165 F15000; wipe and shake\nG1 Y256 ; move Y to aside, prevent collision\nM400\nG1 Z{max_layer_z + 3.0} F3000\n{if layer_z <= (initial_layer_print_height + 0.001)}\nM204 S[initial_layer_acceleration]\n{else}\nM204 S[default_acceleration]\n{endif}\n{else}\nG1 X[x_after_toolchange] Y[y_after_toolchange] Z[z_after_toolchange] F12000\n{endif}\nM621 S[next_extruder]A\n
; close_fan_the_first_x_layers = 1,1
; complete_print_exhaust_fan_speed = 70,70
; cool_plate_temp = 35,35
; cool_plate_temp_initial_layer = 35,35
; curr_bed_type = Textured PEI Plate
; default_acceleration = 10000
; default_filament_colour = ;
; default_filament_profile = "Bambu PLA Basic @BBL X1"
; default_jerk = 0
; default_print_profile = 0.40mm Standard @BBL X1C 0.8 nozzle
; deretraction_speed = 30
; detect_narrow_internal_solid_infill = 1
; detect_overhang_wall = 1
; detect_thin_wall = 0
; draft_shield = disabled
; during_print_exhaust_fan_speed = 70,70
; elefant_foot_compensation = 0.15
; enable_arc_fitting = 1
; enable_overhang_bridge_fan = 1,1
; enable_overhang_speed = 1
; enable_pressure_advance = 0,0
; enable_prime_tower = 0
; enable_support = 0
; enforce_support_layers = 0
; eng_plate_temp = 0,0
; eng_plate_temp_initial_layer = 0,0
; ensure_vertical_shell_thickness = 1
; exclude_object = 1
; extruder_clearance_height_to_lid = 90
; extruder_clearance_height_to_rod = 36
; extruder_clearance_max_radius = 68
; extruder_clearance_radius = 57
; extruder_colour = #018001
; extruder_offset = 0x2
; extruder_type = DirectDrive
; fan_cooling_layer_time = 100,100
; fan_max_speed = 100,100
; fan_min_speed = 100,100
; filament_colour = #00AE42;#FFFF00
; filament_cost = 20,20
; filament_density = 1.24,1.24
; filament_diameter = 1.75,1.75
; filament_end_gcode = "; filament end gcode \nM106 P3 S0\n";"; filament end gcode \nM106 P3 S0\n"
; filament_flow_ratio = 0.98,0.98
; filament_ids = GFL99;GFL99
; filament_is_support = 0,0
; filament_max_volumetric_speed = 12,12
; filament_minimal_purge_on_wipe_tower = 15,15
; filament_settings_id = "Generic PLA";"Generic PLA"
; filament_soluble = 0,0
; filament_start_gcode = "; filament start gcode\n{if  (bed_temperature[current_extruder] >55)||(bed_temperature_initial_layer[current_extruder] >55)}M106 P3 S200\n{elsif(bed_temperature[current_extruder] >50)||(bed_temperature_initial_layer[current_extruder] >50)}M106 P3 S150\n{elsif(bed_temperature[current_extruder] >45)||(bed_temperature_initial_layer[current_extruder] >45)}M106 P3 S50\n{endif}\n\n{if activate_air_filtration[current_extruder] && support_air_filtration}\nM106 P3 S{during_print_exhaust_fan_speed_num[current_extruder]} \n{endif}";"; filament start gcode\n{if  (bed_temperature[current_extruder] >55)||(bed_temperature_initial_layer[current_extruder] >55)}M106 P3 S200\n{elsif(bed_temperature[current_extruder] >50)||(bed_temperature_initial_layer[current_extruder] >50)}M106 P3 S150\n{elsif(bed_temperature[current_extruder] >45)||(bed_temperature_initial_layer[current_extruder] >45)}M106 P3 S50\n{endif}\n\n{if activate_air_filtration[current_extruder] && support_air_filtration}\nM106 P3 S{during_print_exhaust_fan_speed_num[current_extruder]} \n{endif}"
; filament_type = PLA;PLA
; filament_vendor = Generic;Generic
; filename_format = {input_filename_base}_{filament_type[0]}_{print_time}.gcode
; filter_out_gap_fill = 0
; first_layer_print_sequence = 0
; flush_into_infill = 0
; flush_into_objects = 0
; flush_into_support = 1
; flush_multiplier = 1
; flush_volumes_matrix = 0,615,308,0
; flush_volumes_vector = 140,140,140,140
; full_fan_speed_layer = 0,0
; fuzzy_skin = none
; fuzzy_skin_point_distance = 0.8
; fuzzy_skin_thickness = 0.3
; gap_infill_speed = 50
; gcode_add_line_number = 0
; gcode_flavor = marlin
; head_wrap_detect_zone = 
; host_type = octoprint
; hot_plate_temp = 55,55
; hot_plate_temp_initial_layer = 55,55
; independent_support_layer_height = 1
; infill_combination = 0
; infill_direction = 45
; infill_jerk = 9
; infill_wall_overlap = 15%
; initial_layer_acceleration = 500
; initial_layer_flow_ratio = 1
; initial_layer_infill_speed = 55
; initial_layer_jerk = 9
; initial_layer_line_width = 0.82
; initial_layer_print_height = 0.4
; initial_layer_speed = 35
; inner_wall_acceleration = 0
; inner_wall_jerk = 9
; inner_wall_line_width = 0.82
; inner_wall_speed = 150
; interface_shells = 0
; internal_bridge_support_thickness = 0.8
; internal_solid_infill_line_width = 0.82
; internal_solid_infill_pattern = zig-zag
; internal_solid_infill_speed = 150
; ironing_direction = 45
; ironing_flow = 10%
; ironing_pattern = zig-zag
; ironing_spacing = 0.15
; ironing_speed = 30
; ironing_type = no ironing
; is_infill_first = 0
; layer_change_gcode = ; layer num/total_layer_count: {layer_num+1}/[total_layer_count]\nM622.1 S1 ; for prev firware, default turned on\nM1002 judge_flag timelapse_record_flag\nM622 J1\n{if timelapse_type == 0} ; timelapse without wipe tower\nM971 S11 C10 O0\n{elsif timelapse_type == 1} ; timelapse with wipe tower\nG92 E0\nG1 E-[retraction_length] F1800\nG17\nG2 Z{layer_z + 0.4} I0.86 J0.86 P1 F20000 ; spiral lift a little\nG1 X65 Y245 F20000 ; move to safe pos\nG17\nG2 Z{layer_z} I0.86 J0.86 P1 F20000\nG1 Y265 F3000\nM400 P300\nM971 S11 C11 O0\nG92 E0\nG1 E[retraction_length] F300\nG1 X100 F5000\nG1 Y255 F20000\n{endif}\nM623\n; update layer progress\nM73 L{layer_num+1}\nM991 S0 P{layer_num} ;notify layer change
; layer_height = 0.4
; line_width = 0.82
; machine_end_gcode = ;===== date: 20230428 =====================\nM400 ; wait for buffer to clear\nG92 E0 ; zero the extruder\nG1 E-0.8 F1800 ; retract\nG1 Z{max_layer_z + 0.5} F900 ; lower z a little\nG1 X65 Y245 F12000 ; move to safe pos \nG1 Y265 F3000\n\nG1 X65 Y245 F12000\nG1 Y265 F3000\nM140 S0 ; turn off bed\nM106 S0 ; turn off fan\nM106 P2 S0 ; turn off remote part cooling fan\nM106 P3 S0 ; turn off chamber cooling fan\n\nG1 X100 F12000 ; wipe\n; pull back filament to AMS\nM620 S255\nG1 X20 Y50 F12000\nG1 Y-3\nT255\nG1 X65 F12000\nG1 Y265\nG1 X100 F12000 ; wipe\nM621 S255\nM104 S0 ; turn off hotend\n\nM622.1 S1 ; for prev firware, default turned on\nM1002 judge_flag timelapse_record_flag\nM622 J1\n    M400 ; wait all motion done\n    M991 S0 P-1 ;end smooth timelapse at safe pos\n    M400 S3 ;wait for last picture to be taken\nM623; end of "timelapse_record_flag"\n\nM400 ; wait all motion done\nM17 S\nM17 Z0.4 ; lower z motor current to reduce impact if there is something in the bottom\n{if (max_layer_z + 100.0) < 250}\n    G1 Z{max_layer_z + 100.0} F600\n    G1 Z{max_layer_z +98.0}\n{else}\n    G1 Z250 F600\n    G1 Z248\n{endif}\nM400 P100\nM17 R ; restore z current\n\nG90\nG1 X128 Y250 F3600\n\nM220 S100  ; Reset feedrate magnitude\nM201.2 K1.0 ; Reset acc magnitude\nM73.2   R1.0 ;Reset left time magnitude\nM1002 set_gcode_claim_speed_level : 0\n\nM17 X0.8 Y0.8 Z0.5 ; lower motor current to 45% power\n
; machine_load_filament_time = 29
; machine_max_acceleration_e = 5000,5000
; machine_max_acceleration_extruding = 20000,20000
; machine_max_acceleration_retracting = 5000,5000
; machine_max_acceleration_travel = 9000,9000
; machine_max_acceleration_x = 20000,20000
; machine_max_acceleration_y = 20000,20000
; machine_max_acceleration_z = 500,200
; machine_max_jerk_e = 2.5,2.5
; machine_max_jerk_x = 9,9
; machine_max_jerk_y = 9,9
; machine_max_jerk_z = 3,3
; machine_max_speed_e = 30,30
; machine_max_speed_x = 500,200
; machine_max_speed_y = 500,200
; machine_max_speed_z = 20,20
; machine_min_extruding_rate = 0,0
; machine_min_travel_rate = 0,0
; machine_pause_gcode = M400 U1
; machine_start_gcode = ;===== machine: P1S ========================\n;===== date: 20231107 =====================\n;===== turn on the HB fan & MC board fan =================\nM104 S75 ;set extruder temp to turn on the HB fan and prevent filament oozing from nozzle\nM710 A1 S255 ; turn on MC fan by default(P1S)\n;===== reset machine status =================\nM290 X40 Y40 Z2.6666666\nG91\nM17 Z0.4 ; lower the z-motor current\nG380 S2 Z30 F300 ; G380 is same as G38; lower the hotbed , to prevent the nozzle is below the hotbed\nG380 S2 Z-25 F300 ;\nG1 Z5 F300;\nG90\nM17 X1.2 Y1.2 Z0.75 ; reset motor current to default\nM960 S5 P1 ; turn on logo lamp\nG90\nM220 S100 ;Reset Feedrate\nM221 S100 ;Reset Flowrate\nM73.2   R1.0 ;Reset left time magnitude\nM1002 set_gcode_claim_speed_level : 5\nM221 X0 Y0 Z0 ; turn off soft endstop to prevent protential logic problem\nG29.1 Z{+0.0} ; clear z-trim value first\nM204 S10000 ; init ACC set to 10m/s^2\n\n;===== heatbed preheat ====================\nM1002 gcode_claim_action : 2\nM140 S[bed_temperature_initial_layer_single] ;set bed temp\nM190 S[bed_temperature_initial_layer_single] ;wait for bed temp\n\n\n;=============turn on fans to prevent PLA jamming=================\n{if filament_type[initial_extruder]=="PLA"}\n    {if (bed_temperature[initial_extruder] >45)||(bed_temperature_initial_layer[initial_extruder] >45)}\n    M106 P3 S180\n    {elsif (bed_temperature[initial_extruder] >50)||(bed_temperature_initial_layer[initial_extruder] >50)}\n    M106 P3 S255\n    {endif};Prevent PLA from jamming\n{endif}\nM106 P2 S100 ; turn on big fan ,to cool down toolhead\n\n;===== prepare print temperature and material ==========\nM104 S[nozzle_temperature_initial_layer] ;set extruder temp\nG91\nG0 Z10 F1200\nG90\nG28 X\nM975 S1 ; turn on\nG1 X60 F12000\nG1 Y245\nG1 Y265 F3000\nM620 M\nM620 S[initial_extruder]A   ; switch material if AMS exist\n    M109 S[nozzle_temperature_initial_layer]\n    G1 X120 F12000\n\n    G1 X20 Y50 F12000\n    G1 Y-3\n    T[initial_extruder]\n    G1 X54 F12000\n    G1 Y265\n    M400\nM621 S[initial_extruder]A\nM620.1 E F{filament_max_volumetric_speed[initial_extruder]/2.4053*60} T{nozzle_temperature_range_high[initial_extruder]}\n\n\nM412 S1 ; ===turn on filament runout detection===\n\nM109 S250 ;set nozzle to common flush temp\nM106 P1 S0\nG92 E0\nG1 E50 F200\nM400\nM104 S[nozzle_temperature_initial_layer]\nG92 E0\nG1 E50 F200\nM400\nM106 P1 S255\nG92 E0\nG1 E5 F300\nM109 S{nozzle_temperature_initial_layer[initial_extruder]-20} ; drop nozzle temp, make filament shink a bit\nG92 E0\nG1 E-0.5 F300\n\nG1 X70 F9000\nG1 X76 F15000\nG1 X65 F15000\nG1 X76 F15000\nG1 X65 F15000; shake to put down garbage\nG1 X80 F6000\nG1 X95 F15000\nG1 X80 F15000\nG1 X165 F15000; wipe and shake\nM400\nM106 P1 S0\n;===== prepare print temperature and material end =====\n\n\n;===== wipe nozzle ===============================\nM1002 gcode_claim_action : 14\nM975 S1\nM106 S255\nG1 X65 Y230 F18000\nG1 Y264 F6000\nM109 S{nozzle_temperature_initial_layer[initial_extruder]-20}\nG1 X100 F18000 ; first wipe mouth\n\nG0 X135 Y253 F20000  ; move to exposed steel surface edge\nG28 Z P0 T300; home z with low precision,permit 300deg temperature\nG29.2 S0 ; turn off ABL\nG0 Z5 F20000\n\nG1 X60 Y265\nG92 E0\nG1 E-0.5 F300 ; retrack more\nG1 X100 F5000; second wipe mouth\nG1 X70 F15000\nG1 X100 F5000\nG1 X70 F15000\nG1 X100 F5000\nG1 X70 F15000\nG1 X100 F5000\nG1 X70 F15000\nG1 X90 F5000\nG0 X128 Y261 Z-1.5 F20000  ; move to exposed steel surface and stop the nozzle\nM104 S140 ; set temp down to heatbed acceptable\nM106 S255 ; turn on fan (G28 has turn off fan)\n\nM221 S; push soft endstop status\nM221 Z0 ;turn off Z axis endstop\nG0 Z0.5 F20000\nG0 X125 Y259.5 Z-1.01\nG0 X131 F211\nG0 X124\nG0 Z0.5 F20000\nG0 X125 Y262.5\nG0 Z-1.01\nG0 X131 F211\nG0 X124\nG0 Z0.5 F20000\nG0 X125 Y260.0\nG0 Z-1.01\nG0 X131 F211\nG0 X124\nG0 Z0.5 F20000\nG0 X125 Y262.0\nG0 Z-1.01\nG0 X131 F211\nG0 X124\nG0 Z0.5 F20000\nG0 X125 Y260.5\nG0 Z-1.01\nG0 X131 F211\nG0 X124\nG0 Z0.5 F20000\nG0 X125 Y261.5\nG0 Z-1.01\nG0 X131 F211\nG0 X124\nG0 Z0.5 F20000\nG0 X125 Y261.0\nG0 Z-1.01\nG0 X131 F211\nG0 X124\nG0 X128\nG2 I0.5 J0 F300\nG2 I0.5 J0 F300\nG2 I0.5 J0 F300\nG2 I0.5 J0 F300\n\nM109 S140 ; wait nozzle temp down to heatbed acceptable\nG2 I0.5 J0 F3000\nG2 I0.5 J0 F3000\nG2 I0.5 J0 F3000\nG2 I0.5 J0 F3000\n\nM221 R; pop softend status\nG1 Z10 F1200\nM400\nG1 Z10\nG1 F30000\nG1 X230 Y15\nG29.2 S1 ; turn on ABL\n;G28 ; home again after hard wipe mouth\nM106 S0 ; turn off fan , too noisy\n;===== wipe nozzle end ================================\n\n\n;===== bed leveling ==================================\nM1002 judge_flag g29_before_print_flag\nM622 J1\n\n    M1002 gcode_claim_action : 1\n    G29 A X{first_layer_print_min[0]} Y{first_layer_print_min[1]} I{first_layer_print_size[0]} J{first_layer_print_size[1]}\n    M400\n    M500 ; save cali data\n\nM623\n;===== bed leveling end ================================\n\n;===== home after wipe mouth============================\nM1002 judge_flag g29_before_print_flag\nM622 J0\n\n    M1002 gcode_claim_action : 13\n    G28\n\nM623\n;===== home after wipe mouth end =======================\n\nM975 S1 ; turn on vibration supression\n\n\n;=============turn on fans to prevent PLA jamming=================\n{if filament_type[initial_extruder]=="PLA"}\n    {if (bed_temperature[initial_extruder] >45)||(bed_temperature_initial_layer[initial_extruder] >45)}\n    M106 P3 S180\n    {elsif (bed_temperature[initial_extruder] >50)||(bed_temperature_initial_layer[initial_extruder] >50)}\n    M106 P3 S255\n    {endif};Prevent PLA from jamming\n{endif}\nM106 P2 S100 ; turn on big fan ,to cool down toolhead\n\n\nM104 S{nozzle_temperature_initial_layer[initial_extruder]} ; set extrude temp earlier, to reduce wait time\n\n;===== mech mode fast check============================\nG1 X128 Y128 Z10 F20000\nM400 P200\nM970.3 Q1 A7 B30 C80  H15 K0\nM974 Q1 S2 P0\n\nG1 X128 Y128 Z10 F20000\nM400 P200\nM970.3 Q0 A7 B30 C90 Q0 H15 K0\nM974 Q0 S2 P0\n\nM975 S1\nG1 F30000\nG1 X230 Y15\nG28 X ; re-home XY\n;===== fmech mode fast check============================\n\n\n;===== noozle load line ===============================\nM975 S1\nG90\nM83\nT1000\nG1 X18.0 Y0.5 Z0.8 F18000;Move to start position\nM109 S{nozzle_temperature_initial_layer[initial_extruder]}\nG1 Z0.2\nG0 E2 F300\nG0 X129 E15 F{outer_wall_volumetric_speed/(0.3*1.0)     * 60}\nG0 X240 E15\nG0 Y15 E1.500 F{outer_wall_volumetric_speed/(0.3*1.0)/ 4 * 60}\nG0 X239.5\nG0 E0.3\nG0 Y1.5 E1.500\nG0 X129 E15 F{outer_wall_volumetric_speed/(0.3*1.0)     * 60}\nG0 X18 E15\nM400\n\n;===== for Textured PEI Plate , lower the nozzle as the nozzle was touching topmost of the texture when homing ==\n;curr_bed_type={curr_bed_type}\n{if curr_bed_type=="Textured PEI Plate"}\nG29.1 Z{-0.04} ; for Textured PEI Plate\n{endif}\n;========turn off light and wait extrude temperature =============\nM1002 gcode_claim_action : 0\nM106 S0 ; turn off fan\nM106 P2 S0 ; turn off big fan\nM106 P3 S0 ; turn off chamber fan\n\nM975 S1 ; turn on mech mode supression\n
; machine_unload_filament_time = 28
; max_bridge_length = 10
; max_layer_height = 0.56
; max_travel_detour_distance = 0
; min_bead_width = 85%
; min_feature_size = 25%
; min_layer_height = 0.16
; minimum_sparse_infill_area = 15
; mmu_segmented_region_interlocking_depth = 0
; mmu_segmented_region_max_width = 0
; nozzle_diameter = 0.8
; nozzle_temperature = 220,220
; nozzle_temperature_initial_layer = 220,220
; nozzle_temperature_range_high = 240,240
; nozzle_temperature_range_low = 190,190
; nozzle_type = hardened_steel
; nozzle_volume = 107
; only_one_wall_first_layer = 0
; ooze_prevention = 0
; outer_wall_acceleration = 5000
; outer_wall_jerk = 9
; outer_wall_line_width = 0.82
; outer_wall_speed = 120
; overhang_1_4_speed = 0
; overhang_2_4_speed = 50
; overhang_3_4_speed = 25
; overhang_4_4_speed = 5
; overhang_fan_speed = 100,100
; overhang_fan_threshold = 50%,50%
; post_process = 
; pressure_advance = 0.02,0.02
; prime_tower_brim_width = 3
; prime_tower_width = 35
; prime_volume = 45
; print_compatible_printers = "Bambu Lab X1 Carbon 0.8 nozzle";"Bambu Lab P1S 0.8 nozzle";"Bambu Lab X1E 0.8 nozzle"
; print_flow_ratio = 1
; print_host = 
; print_host_webui = 
; print_sequence = by layer
; print_settings_id = 0.40mm Standard @BBL X1C 0.8 nozzle
; printable_area = 0x0,256x0,256x256,0x256
; printable_height = 250
; printer_model = Bambu Lab P1S
; printer_settings_id = Bambu Lab P1S 0.8 nozzle
; printer_structure = corexy
; printer_technology = FFF
; printer_variant = 0.8
; printhost_apikey = 
; printhost_authorization_type = key
; printhost_cafile = 
; printhost_password = 
; printhost_port = 
; printhost_ssl_ignore_revoke = 0
; printhost_user = 
; printing_by_object_gcode = 
; raft_contact_distance = 0.1
; raft_expansion = 1.5
; raft_first_layer_density = 90%
; raft_first_layer_expansion = 2
; raft_layers = 0
; reduce_crossing_wall = 0
; reduce_fan_stop_start_freq = 1,1
; reduce_infill_retraction = 1
; required_nozzle_HRC = 3,3
; resolution = 0.012
; retract_before_wipe = 0%
; retract_length_toolchange = 3
; retract_lift_above = 0
; retract_lift_below = 249
; retract_restart_extra = 0
; retract_restart_extra_toolchange = 0
; retract_when_changing_layer = 1
; retraction_length = 3
; retraction_minimum_travel = 1
; retraction_speed = 30
; scan_first_layer = 0
; seam_gap = 15%
; seam_position = aligned
; silent_mode = 0
; single_extruder_multi_material = 1
; skirt_distance = 2
; skirt_height = 1
; skirt_loops = 0
; slice_closing_radius = 0.049
; slicing_mode = regular
; slow_down_for_layer_cooling = 1,1
; slow_down_layer_time = 8,8
; slow_down_min_speed = 20,20
; small_perimeter_speed = 50%
; small_perimeter_threshold = 0
; solid_infill_filament = 1
; sparse_infill_acceleration = 100%
; sparse_infill_anchor = 400%
; sparse_infill_anchor_max = 20
; sparse_infill_density = 15%
; sparse_infill_filament = 1
; sparse_infill_line_width = 0.82
; sparse_infill_pattern = grid
; sparse_infill_speed = 100
; spiral_mode = 0
; standby_temperature_delta = -5
; start_end_points = 30x-3,54x245
; support_air_filtration = 0
; support_angle = 0
; support_base_pattern = default
; support_base_pattern_spacing = 2.5
; support_bottom_interface_spacing = 0.5
; support_bottom_z_distance = 0.2
; support_chamber_temp_control = 0
; support_critical_regions_only = 0
; support_expansion = 0
; support_filament = 0
; support_interface_bottom_layers = 2
; support_interface_filament = 0
; support_interface_loop_pattern = 0
; support_interface_not_for_body = 1
; support_interface_pattern = auto
; support_interface_spacing = 0.5
; support_interface_speed = 80
; support_interface_top_layers = 2
; support_line_width = 0.82
; support_object_xy_distance = 0.35
; support_on_build_plate_only = 0
; support_remove_small_overhang = 1
; support_speed = 150
; support_style = default
; support_threshold_angle = 30
; support_top_z_distance = 0.2
; support_type = normal(auto)
; temperature_vitrification = 45,45
; template_custom_gcode = 
; textured_plate_temp = 55,55
; textured_plate_temp_initial_layer = 55,55
; thick_bridges = 0
; thumbnail_size = 50x50
; time_lapse_gcode = 
; timelapse_type = 0
; top_area_threshold = 100%
; top_one_wall_type = all top
; top_shell_layers = 3
; top_shell_thickness = 0.8
; top_solid_infill_flow_ratio = 1
; top_surface_acceleration = 2000
; top_surface_jerk = 9
; top_surface_line_width = 0.82
; top_surface_pattern = monotonic
; top_surface_speed = 150
; travel_jerk = 9
; travel_speed = 500
; travel_speed_z = 0
; tree_support_branch_angle = 45
; tree_support_branch_diameter = 2
; tree_support_branch_distance = 5
; tree_support_brim_width = 0
; tree_support_wall_count = 0
; upward_compatible_machine = "Bambu Lab P1P 0.8 nozzle";"Bambu Lab X1 0.8 nozzle";"Bambu Lab X1 Carbon 0.8 nozzle";"Bambu Lab X1E 0.8 nozzle";"Bambu Lab A1 0.8 nozzle"
; use_firmware_retraction = 0
; use_relative_e_distances = 1
; wall_distribution_count = 1
; wall_filament = 1
; wall_generator = classic
; wall_loops = 2
; wall_sequence = inner wall/outer wall
; wall_transition_angle = 10
; wall_transition_filter_deviation = 25%
; wall_transition_length = 100%
; wipe = 1
; wipe_distance = 2
; wipe_speed = 80%
; wipe_tower_no_sparse_layers = 0
; wipe_tower_rotation_angle = 0
; wipe_tower_x = 165
; wipe_tower_y = 241
; xy_contour_compensation = 0
; xy_hole_compensation = 0
; z_hop = 0.4
; z_hop_types = Auto Lift
; CONFIG_BLOCK_END

; EXECUTABLE_BLOCK_START
M73 P0 R10
M201 X20000 Y20000 Z500 E5000
M203 X500 Y500 Z20 E30
M204 P20000 R5000 T20000
M205 X9.00 Y9.00 Z3.00 E2.50
M106 S0
M106 P2 S0
; FEATURE: Custom
;===== machine: P1S ========================
;===== date: 20231107 =====================
;===== turn on the HB fan & MC board fan =================
M104 S75 ;set extruder temp to turn on the HB fan and prevent filament oozing from nozzle
M710 A1 S255 ; turn on MC fan by default(P1S)
;===== reset machine status =================
M290 X40 Y40 Z2.6666666
G91
M17 Z0.4 ; lower the z-motor current
G380 S2 Z30 F300 ; G380 is same as G38; lower the hotbed , to prevent the nozzle is below the hotbed
G380 S2 Z-25 F300 ;
G1 Z5 F300;
G90
M17 X1.2 Y1.2 Z0.75 ; reset motor current to default
M960 S5 P1 ; turn on logo lamp
G90
M220 S100 ;Reset Feedrate
M221 S100 ;Reset Flowrate
M73.2   R1.0 ;Reset left time magnitude
M1002 set_gcode_claim_speed_level : 5
M221 X0 Y0 Z0 ; turn off soft endstop to prevent protential logic problem
G29.1 Z0 ; clear z-trim value first
M204 S10000 ; init ACC set to 10m/s^2

;===== heatbed preheat ====================
M1002 gcode_claim_action : 2
M140 S55 ;set bed temp
M190 S55 ;wait for bed temp


;=============turn on fans to prevent PLA jamming=================

    
    M106 P3 S180
    ;Prevent PLA from jamming

M106 P2 S100 ; turn on big fan ,to cool down toolhead

;===== prepare print temperature and material ==========
M104 S220 ;set extruder temp
G91
G0 Z10 F1200
G90
G28 X
M975 S1 ; turn on
M73 P41 R6
G1 X60 F12000
G1 Y245
G1 Y265 F3000
M620 M
M620 S0A   ; switch material if AMS exist
    M109 S220
    G1 X120 F12000

M73 P42 R6
    G1 X20 Y50 F12000
    G1 Y-3
    T0
    G1 X54 F12000
    G1 Y265
    M400
M621 S0A
M620.1 E F299.339 T240


M412 S1 ; ===turn on filament runout detection===

M109 S250 ;set nozzle to common flush temp
M106 P1 S0
G92 E0
G1 E50 F200
M400
M104 S220
G92 E0
G1 E50 F200
M400
M106 P1 S255
G92 E0
M73 P42 R5
G1 E5 F300
M109 S200 ; drop nozzle temp, make filament shink a bit
G92 E0
M73 P45 R5
G1 E-0.5 F300

M73 P47 R5
G1 X70 F9000
G1 X76 F15000
G1 X65 F15000
G1 X76 F15000
G1 X65 F15000; shake to put down garbage
G1 X80 F6000
G1 X95 F15000
G1 X80 F15000
G1 X165 F15000; wipe and shake
M400
M106 P1 S0
;===== prepare print temperature and material end =====


;===== wipe nozzle ===============================
M1002 gcode_claim_action : 14
M975 S1
M106 S255
G1 X65 Y230 F18000
G1 Y264 F6000
M109 S200
G1 X100 F18000 ; first wipe mouth

G0 X135 Y253 F20000  ; move to exposed steel surface edge
G28 Z P0 T300; home z with low precision,permit 300deg temperature
G29.2 S0 ; turn off ABL
G0 Z5 F20000

G1 X60 Y265
G92 E0
G1 E-0.5 F300 ; retrack more
G1 X100 F5000; second wipe mouth
G1 X70 F15000
M73 P48 R5
G1 X100 F5000
G1 X70 F15000
G1 X100 F5000
G1 X70 F15000
G1 X100 F5000
G1 X70 F15000
G1 X90 F5000
G0 X128 Y261 Z-1.5 F20000  ; move to exposed steel surface and stop the nozzle
M104 S140 ; set temp down to heatbed acceptable
M106 S255 ; turn on fan (G28 has turn off fan)

M221 S; push soft endstop status
M221 Z0 ;turn off Z axis endstop
G0 Z0.5 F20000
G0 X125 Y259.5 Z-1.01
G0 X131 F211
G0 X124
G0 Z0.5 F20000
G0 X125 Y262.5
G0 Z-1.01
G0 X131 F211
G0 X124
G0 Z0.5 F20000
G0 X125 Y260.0
G0 Z-1.01
G0 X131 F211
G0 X124
G0 Z0.5 F20000
G0 X125 Y262.0
G0 Z-1.01
G0 X131 F211
G0 X124
G0 Z0.5 F20000
G0 X125 Y260.5
G0 Z-1.01
G0 X131 F211
G0 X124
G0 Z0.5 F20000
G0 X125 Y261.5
G0 Z-1.01
G0 X131 F211
G0 X124
G0 Z0.5 F20000
G0 X125 Y261.0
G0 Z-1.01
G0 X131 F211
G0 X124
G0 X128
G2 I0.5 J0 F300
G2 I0.5 J0 F300
G2 I0.5 J0 F300
G2 I0.5 J0 F300

M109 S140 ; wait nozzle temp down to heatbed acceptable
G2 I0.5 J0 F3000
G2 I0.5 J0 F3000
G2 I0.5 J0 F3000
G2 I0.5 J0 F3000

M221 R; pop softend status
G1 Z10 F1200
M400
G1 Z10
M73 P49 R5
G1 F30000
G1 X230 Y15
G29.2 S1 ; turn on ABL
;G28 ; home again after hard wipe mouth
M106 S0 ; turn off fan , too noisy
;===== wipe nozzle end ================================


;===== bed leveling ==================================
M1002 judge_flag g29_before_print_flag
M622 J1

    M1002 gcode_claim_action : 1
    G29 A X118.49 Y118.49 I19.0198 J19.0198
    M400
    M500 ; save cali data

M623
;===== bed leveling end ================================

;===== home after wipe mouth============================
M1002 judge_flag g29_before_print_flag
M622 J0

    M1002 gcode_claim_action : 13
    G28

M623
;===== home after wipe mouth end =======================

M975 S1 ; turn on vibration supression


;=============turn on fans to prevent PLA jamming=================

    
    M106 P3 S180
    ;Prevent PLA from jamming

M106 P2 S100 ; turn on big fan ,to cool down toolhead


M104 S220 ; set extrude temp earlier, to reduce wait time

;===== mech mode fast check============================
G1 X128 Y128 Z10 F20000
M400 P200
M970.3 Q1 A7 B30 C80  H15 K0
M974 Q1 S2 P0

G1 X128 Y128 Z10 F20000
M400 P200
M970.3 Q0 A7 B30 C90 Q0 H15 K0
M974 Q0 S2 P0

M975 S1
G1 F30000
G1 X230 Y15
G28 X ; re-home XY
;===== fmech mode fast check============================


;===== noozle load line ===============================
M975 S1
G90
M83
T1000
G1 X18.0 Y0.5 Z0.8 F18000;Move to start position
M109 S220
G1 Z0.2
G0 E2 F300
G0 X129 E15 F2400
G0 X240 E15
G0 Y15 E1.500 F600
G0 X239.5
G0 E0.3
G0 Y1.5 E1.500
G0 X129 E15 F2400
G0 X18 E15
M400

;===== for Textured PEI Plate , lower the nozzle as the nozzle was touching topmost of the texture when homing ==
;curr_bed_type=Textured PEI Plate

G29.1 Z-0.04 ; for Textured PEI Plate

;========turn off light and wait extrude temperature =============
M1002 gcode_claim_action : 0
M106 S0 ; turn off fan
M106 P2 S0 ; turn off big fan
M106 P3 S0 ; turn off chamber fan

M975 S1 ; turn on mech mode supression
G90
G21
M83 ; use relative distances for extrusion
; filament start gcode
M106 P3 S150


M981 S1 P20000 ;open spaghetti detector
; CHANGE_LAYER
; Z_HEIGHT: 0.4
; LAYER_HEIGHT: 0.4
G1 E-3 F1800
; layer num/total_layer_count: 1/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L1
M991 S0 P0 ;notify layer change
M106 S0
M106 P2 S0
M204 S500
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
M73 P50 R5
G1 X131.499 Y123.122 F30000
G1 Z.4
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2100
G1 X131.594 Y123.211 E.01554
G1 X131.594 Y128.789 E.66751
M73 P51 R5
G1 X130.876 Y129.456 E.11718
G3 X127.727 Y121.512 I-2.872 J-3.457 E2.02887
G3 X130.876 Y122.544 I.244 J4.578 E.40575
G1 X131.411 Y123.041 E.08728
G1 X130.86 Y123.544 F30000
; FEATURE: Outer wall
G1 F2100
G1 X130.86 Y128.469 E.58929
G1 X130.406 Y128.891 E.07412
G3 X127.771 Y122.246 I-2.402 J-2.892 E1.6971
M73 P52 R4
G3 X128.579 Y122.284 I.222 J3.899 E.09691
G3 X130.786 Y123.453 I-.718 J4.023 E.30377
; WIPE_START
G1 F24000
G1 X130.816 Y125.453 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.217 Y126.166 Z.8 F30000
M73 P53 R4
G1 X122.388 Y126.244 Z.8
G1 Z.4
G1 E3 F1800
; FEATURE: Inner wall
G1 F2100
G1 X122.37 Y126.167 E.00948
G1 X122.584 Y124.938 E.14918
G1 X122.667 Y124.578 E.04422
G1 X123.041 Y123.329 E.15599
G1 X123.84 Y122.373 E.14919
G1 X124.092 Y122.102 E.04422
G1 X125.04 Y121.207 E.156
G1 X126.211 Y120.779 E.14918
G1 X126.565 Y120.671 E.04422
G1 X127.833 Y120.37 E.15599
G1 X129.062 Y120.584 E.14918
M73 P54 R4
G1 X129.422 Y120.667 E.04422
G1 X130.671 Y121.041 E.15599
G1 X131.627 Y121.84 E.14919
G1 X131.898 Y122.093 E.04422
G1 X132.793 Y123.04 E.15599
G1 X133.221 Y124.211 E.14918
G1 X133.329 Y124.565 E.04422
G1 X133.63 Y125.833 E.15599
G1 X133.416 Y127.062 E.14918
M73 P55 R4
G1 X133.333 Y127.422 E.04422
G1 X132.959 Y128.671 E.15599
G1 X132.16 Y129.627 E.14919
G1 X131.907 Y129.898 E.04422
G1 X130.96 Y130.793 E.15599
M73 P56 R4
G1 X129.789 Y131.221 E.14918
G1 X129.435 Y131.329 E.04422
G1 X128.167 Y131.63 E.15599
G1 X126.938 Y131.416 E.14918
G1 X126.578 Y131.333 E.04422
G1 X125.329 Y130.959 E.15599
G1 X124.373 Y130.16 E.14919
G1 X124.102 Y129.908 E.04422
G1 X123.207 Y128.96 E.15599
G1 X122.779 Y127.789 E.14918
G1 X122.671 Y127.435 E.04422
G1 X122.416 Y126.361 E.13216
G1 X121.782 Y126.872 F30000
; FEATURE: Outer wall
G1 F2100
G3 X119.059 Y126.376 I-.07 J-7.349 E.33315
G3 X119.051 Y125.873 I5.28 J-.343 E.06025
M73 P57 R4
G3 X121.778 Y125.288 I2.937 J7.045 E.33558
G3 X122.18 Y123.646 I9.437 J1.44 E.20257
G3 X120.069 Y121.856 I3.614 J-6.399 E.33315
G3 X120.313 Y121.415 I4.744 J2.343 E.06025
G3 X122.967 Y122.272 I-.978 J7.566 E.33558
G3 X124.136 Y121.051 I7.451 J5.964 E.20257
G3 X123.204 Y118.445 I6.329 J-3.735 E.33315
G3 X123.635 Y118.186 I2.937 J4.402 E.06025
G3 X125.505 Y120.255 I-4.63 J6.063 E.33558
G3 X127.128 Y119.783 I3.471 J8.892 E.20257
G3 X127.624 Y117.059 I7.349 J-.07 E.33315
G3 X128.127 Y117.051 I.343 J5.28 E.06025
G3 X128.712 Y119.778 I-7.045 J2.937 E.33558
G3 X130.354 Y120.18 I-1.44 J9.437 E.20257
G3 X132.144 Y118.069 I6.399 J3.614 E.33315
G3 X132.585 Y118.313 I-2.344 J4.744 E.06025
G3 X131.728 Y120.967 I-7.566 J-.978 E.33558
G3 X132.949 Y122.136 I-5.964 J7.451 E.20257
G3 X135.555 Y121.204 I3.735 J6.329 E.33315
G3 X135.814 Y121.635 I-4.401 J2.937 E.06025
G3 X133.745 Y123.505 I-6.063 J-4.63 E.33558
G3 X134.218 Y125.128 I-8.892 J3.471 E.20256
G3 X136.941 Y125.624 I.07 J7.349 E.33315
G3 X136.949 Y126.127 I-5.28 J.343 E.06025
G3 X134.222 Y126.712 I-2.937 J-7.045 E.33558
G3 X133.82 Y128.354 I-9.437 J-1.44 E.20257
G3 X135.931 Y130.144 I-3.614 J6.399 E.33315
G3 X135.687 Y130.585 I-4.744 J-2.343 E.06025
G3 X133.033 Y129.728 I.978 J-7.566 E.33558
G3 X131.864 Y130.949 I-7.451 J-5.964 E.20257
G3 X132.796 Y133.555 I-6.329 J3.735 E.33315
G3 X132.365 Y133.814 I-2.937 J-4.402 E.06025
G3 X130.495 Y131.745 I4.63 J-6.063 E.33558
G3 X128.872 Y132.218 I-3.471 J-8.892 E.20257
G3 X128.376 Y134.941 I-7.349 J.07 E.33315
G3 X127.873 Y134.949 I-.343 J-5.28 E.06025
G3 X127.288 Y132.222 I7.045 J-2.937 E.33558
G3 X125.646 Y131.82 I1.44 J-9.437 E.20257
G3 X123.856 Y133.931 I-6.399 J-3.614 E.33315
G3 X123.415 Y133.687 I2.343 J-4.744 E.06025
G3 X124.272 Y131.033 I7.566 J.978 E.33558
G3 X123.051 Y129.864 I5.964 J-7.451 E.20257
G3 X120.445 Y130.796 I-3.735 J-6.329 E.33315
G3 X120.186 Y130.365 I4.401 J-2.937 E.06025
G3 X122.255 Y128.495 I6.063 J4.63 E.33558
G3 X121.806 Y126.989 I8.892 J-3.471 E.18821
G1 X122.005 Y126.509 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 0.635065
G1 F2100
G1 X121.94 Y126.443 E.00835
; LINE_WIDTH: 0.676736
G1 X121.874 Y126.377 E.00898
; LINE_WIDTH: 0.718408
G1 X121.808 Y126.31 E.00962
; LINE_WIDTH: 0.76008
G1 X121.743 Y126.244 E.01025
; LINE_WIDTH: 0.801752
G1 X121.677 Y126.178 E.01088
; LINE_WIDTH: 0.843424
G1 X121.612 Y126.111 E.01152
; LINE_WIDTH: 0.899011
G1 X121.591 Y126.086 E.0043
G1 X121.328 Y126.093 E.03487
; LINE_WIDTH: 0.87337
G1 X121.141 Y126.094 E.02402
; LINE_WIDTH: 0.848282
G1 X121.024 Y126.098 E.01453
; LINE_WIDTH: 0.81441
G1 X120.84 Y126.099 E.02179
; LINE_WIDTH: 0.77411
G1 X120.719 Y126.102 E.0136
; LINE_WIDTH: 0.740939
G1 X120.084 Y126.104 E.06781
; LINE_WIDTH: 0.725591
G1 X119.449 Y126.107 E.06622
; WIPE_START
G1 F24000
G1 X120.084 Y126.104 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X122.955 Y126.01 Z.8 F30000
G1 Z.4
G1 E3 F1800
; LINE_WIDTH: 0.432241
G1 F2100
G3 X122.986 Y125.729 I5.201 J.44 E.01593
; LINE_WIDTH: 0.399887
G1 X123.016 Y125.468 E.01344
; LINE_WIDTH: 0.37871
G3 X123.108 Y124.936 I23.822 J3.86 E.02579
G1 X123.165 Y124.71 E.01111
; LINE_WIDTH: 0.390587
G3 X123.433 Y123.888 I13.834 J4.052 E.04298
; LINE_WIDTH: 0.455799
G3 X123.671 Y123.421 I1.254 J.346 E.03183
; LINE_WIDTH: 0.421244
G3 X123.84 Y123.195 I4.248 J3.006 E.01538
; LINE_WIDTH: 0.39321
G1 X123.998 Y122.986 E.01315
; LINE_WIDTH: 0.380566
G3 X124.948 Y122.019 I4.787 J3.756 E.06525
; LINE_WIDTH: 0.418574
G1 X125.148 Y121.849 E.01423
; LINE_WIDTH: 0.433517
G1 X125.163 Y121.837 E.00107
; LINE_WIDTH: 0.462702
G3 X125.479 Y121.634 I.652 J.667 E.02324
; LINE_WIDTH: 0.439292
G1 X125.613 Y121.569 E.0086
; LINE_WIDTH: 0.40006
G3 X126.114 Y121.36 I4.126 J9.177 E.02781
; LINE_WIDTH: 0.381993
G3 X127.425 Y121.012 I2.186 J5.601 E.06558
; LINE_WIDTH: 0.429338
G1 X127.684 Y120.967 E.0147
; LINE_WIDTH: 0.464299
G3 X128.03 Y120.961 I.192 J1.149 E.02147
; LINE_WIDTH: 0.43329
G1 X128.21 Y120.976 E.01021
; LINE_WIDTH: 0.384274
G3 X129.808 Y121.323 I-.718 J7.157 E.07971
; LINE_WIDTH: 0.405095
G3 X130.07 Y121.421 I-1.67 J4.892 E.01452
; LINE_WIDTH: 0.441351
G1 X130.316 Y121.512 E.01522
; LINE_WIDTH: 0.462952
G3 X130.585 Y121.679 I-.308 J.797 E.01957
; LINE_WIDTH: 0.423259
G1 X130.772 Y121.811 E.01258
; LINE_WIDTH: 0.388473
G3 X131.197 Y122.147 I-6 J8.052 E.02672
; LINE_WIDTH: 0.355788
G3 X132.044 Y122.961 I-12.258 J13.6 E.0517
G1 X132.796 Y124.116 E.06063
G1 X132.362 Y124.1 F30000
; LINE_WIDTH: 0.832991
G1 F2100
M73 P58 R4
G1 X132.32 Y123.859 E.02986
; LINE_WIDTH: 0.788892
G1 X132.277 Y123.617 E.02809
; LINE_WIDTH: 0.744794
G1 X132.234 Y123.376 E.02633
; LINE_WIDTH: 0.700696
G1 X132.191 Y123.134 E.02457
; LINE_WIDTH: 0.678647
G1 X132.148 Y122.893 E.02369
G1 X132.937 Y122.561 F30000
; LINE_WIDTH: 0.664166
G1 F2100
G1 X133.045 Y122.591 E.01055
; LINE_WIDTH: 0.689164
G1 X133.153 Y122.621 E.01101
; LINE_WIDTH: 0.73916
G1 X133.261 Y122.65 E.01192
; LINE_WIDTH: 0.789157
G1 X133.369 Y122.68 E.01283
; LINE_WIDTH: 0.839153
G1 X133.477 Y122.709 E.01374
; LINE_WIDTH: 0.899008
G1 X133.507 Y122.721 E.00431
G1 X133.731 Y122.583 E.03487
; LINE_WIDTH: 0.873373
G1 X133.893 Y122.489 E.02402
; LINE_WIDTH: 0.848281
G1 X133.993 Y122.427 E.01453
; LINE_WIDTH: 0.81441
G1 X134.151 Y122.335 E.02178
; LINE_WIDTH: 0.774116
G1 X134.254 Y122.271 E.0136
; LINE_WIDTH: 0.740577
G1 X134.803 Y121.952 E.06777
; LINE_WIDTH: 0.70915
G1 X135.352 Y121.632 E.06452
; WIPE_START
G1 F24000
G1 X134.803 Y121.952 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X132.362 Y124.1 Z.8 F30000
G1 Z.4
G1 E3 F1800
; LINE_WIDTH: 0.877089
G1 F2100
G1 X132.405 Y124.341 E.03162
; LINE_WIDTH: 0.921187
G1 X132.448 Y124.583 E.03338
; LINE_WIDTH: 0.965286
G1 F2046.746
G1 X132.491 Y124.824 E.03514
G1 X131.888 Y125.563 F30000
; FEATURE: Bottom surface
; LINE_WIDTH: 0.966832
G1 F2043.154
G1 X133.158 Y126.833 E.25789
G1 X132.497 Y127.066 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 0.99827
G1 F1972.756
G1 X132.441 Y127.45 E.05777
; LINE_WIDTH: 0.951842
G1 F2078.52
G1 X132.384 Y127.835 E.05483
; LINE_WIDTH: 0.905413
G1 F2100
G1 X132.328 Y128.219 E.05189
; LINE_WIDTH: 0.858985
G1 X132.272 Y128.604 E.04895
; LINE_WIDTH: 0.835771
G1 X132.216 Y128.988 E.04748
G1 X132.086 Y128.95 F30000
; LINE_WIDTH: 0.343354
G1 F2100
G1 X132.036 Y129.03 E.00398
G1 X131.784 Y129.296 E.01535
; LINE_WIDTH: 0.365037
G1 X131.544 Y129.536 E.01547
; LINE_WIDTH: 0.385758
G3 X130.999 Y130.026 I-4.921 J-4.923 E.03584
; LINE_WIDTH: 0.427992
G1 X130.798 Y130.195 E.01464
; LINE_WIDTH: 0.463761
G3 X130.489 Y130.381 I-.78 J-.945 E.02225
; LINE_WIDTH: 0.431903
G1 X130.323 Y130.459 E.0104
; LINE_WIDTH: 0.386826
G3 X128.506 Y130.999 I-2.816 J-6.148 E.09326
; LINE_WIDTH: 0.43986
G1 X128.247 Y131.043 E.01516
; LINE_WIDTH: 0.463314
G3 X127.926 Y131.035 I-.138 J-.877 E.01987
; LINE_WIDTH: 0.424151
G1 X127.703 Y131.015 E.01235
; LINE_WIDTH: 0.382852
G3 X126.126 Y130.654 I.768 J-6.988 E.07847
; LINE_WIDTH: 0.412938
G3 X125.865 Y130.555 I1.712 J-4.905 E.0149
; LINE_WIDTH: 0.452968
G1 X125.619 Y130.461 E.01573
; LINE_WIDTH: 0.457697
G1 X125.386 Y130.3 E.01718
; LINE_WIDTH: 0.416954
G1 X125.172 Y130.147 E.01419
; LINE_WIDTH: 0.382635
G3 X123.999 Y129.034 I4.085 J-5.481 E.0784
; LINE_WIDTH: 0.420579
G3 X123.843 Y128.839 I3.548 J-3.011 E.01365
; LINE_WIDTH: 0.460019
G1 X123.697 Y128.657 E.01422
; LINE_WIDTH: 0.471804
G1 X123.67 Y128.603 E.00378
; LINE_WIDTH: 0.444483
G3 X123.554 Y128.345 I4.72 J-2.263 E.01655
; LINE_WIDTH: 0.407797
G1 X123.447 Y128.105 E.01379
; LINE_WIDTH: 0.38351
G3 X123.002 Y126.532 I6.222 J-2.614 E.07948
; LINE_WIDTH: 0.451961
G1 X122.946 Y126.149 E.02309
G1 X122.955 Y126.01 E.00834
; WIPE_START
G1 F24000
G1 X122.946 Y126.149 E-.75612
G1 X123.002 Y126.532 E-2.09388
; WIPE_END
G1 E-.15 F1800
G1 X122.554 Y123.444 Z.8 F30000
G1 Z.4
G1 E3 F1800
; LINE_WIDTH: 0.639167
G1 F2100
G1 X122.525 Y123.335 E.01009
; LINE_WIDTH: 0.689164
G1 X122.497 Y123.227 E.01101
; LINE_WIDTH: 0.73916
G1 X122.469 Y123.119 E.01192
; LINE_WIDTH: 0.789157
G1 X122.44 Y123.011 E.01283
; LINE_WIDTH: 0.839153
G1 X122.412 Y122.902 E.01374
; LINE_WIDTH: 0.899005
G1 X122.407 Y122.87 E.00431
G1 X122.175 Y122.745 E.03488
; LINE_WIDTH: 0.873372
G1 X122.013 Y122.652 E.02402
; LINE_WIDTH: 0.848282
G1 X121.91 Y122.597 E.01453
; LINE_WIDTH: 0.814407
G1 X121.75 Y122.506 E.02179
; LINE_WIDTH: 0.774116
G1 X121.644 Y122.448 E.0136
; LINE_WIDTH: 0.740582
G1 X121.092 Y122.133 E.06777
; LINE_WIDTH: 0.724867
G1 X120.541 Y121.817 E.06614
; WIPE_START
G1 F24000
G1 X121.092 Y122.133 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X124.561 Y121.063 Z.8 F30000
G1 Z.4
G1 E3 F1800
; LINE_WIDTH: 0.63509
G1 F2100
G1 X124.586 Y120.973 E.00835
; LINE_WIDTH: 0.676762
G1 X124.611 Y120.883 E.00898
; LINE_WIDTH: 0.718435
G1 X124.635 Y120.793 E.00962
; LINE_WIDTH: 0.760107
G1 X124.66 Y120.703 E.01025
; LINE_WIDTH: 0.801779
G1 X124.685 Y120.613 E.01089
; LINE_WIDTH: 0.843451
G1 X124.71 Y120.523 E.01152
; LINE_WIDTH: 0.899018
G1 X124.721 Y120.493 E.0043
G1 X124.583 Y120.269 E.03487
; LINE_WIDTH: 0.873374
G1 X124.489 Y120.107 E.02402
; LINE_WIDTH: 0.848285
G1 X124.427 Y120.007 E.01453
; LINE_WIDTH: 0.814411
G1 X124.335 Y119.849 E.02179
; LINE_WIDTH: 0.774115
G1 X124.271 Y119.746 E.0136
; LINE_WIDTH: 0.740576
G1 X123.952 Y119.197 E.06777
; LINE_WIDTH: 0.724862
G1 X123.632 Y118.648 E.06614
; WIPE_START
G1 F24000
G1 X123.952 Y119.197 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X127.491 Y120.005 Z.8 F30000
G1 Z.4
G1 E3 F1800
; LINE_WIDTH: 0.655927
G1 F2100
G1 X127.557 Y119.94 E.00867
; LINE_WIDTH: 0.676764
G1 X127.623 Y119.874 E.00898
; LINE_WIDTH: 0.718437
G1 X127.69 Y119.808 E.00962
; LINE_WIDTH: 0.76011
G1 X127.756 Y119.743 E.01025
; LINE_WIDTH: 0.801783
G1 X127.822 Y119.677 E.01089
; LINE_WIDTH: 0.843456
G1 X127.889 Y119.612 E.01152
; LINE_WIDTH: 0.899014
G1 X127.914 Y119.591 E.0043
G1 X127.907 Y119.328 E.03487
; LINE_WIDTH: 0.87337
G1 X127.906 Y119.141 E.02402
; LINE_WIDTH: 0.848282
G1 X127.902 Y119.024 E.01453
; LINE_WIDTH: 0.81441
G1 X127.901 Y118.84 E.02179
; LINE_WIDTH: 0.77411
G1 X127.898 Y118.719 E.0136
; LINE_WIDTH: 0.740939
G1 X127.896 Y118.084 E.06781
; LINE_WIDTH: 0.710246
G1 X127.893 Y117.449 E.06463
; WIPE_START
G1 F24000
G1 X127.896 Y118.084 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X130.556 Y120.554 Z.8 F30000
G1 Z.4
G1 E3 F1800
; LINE_WIDTH: 0.664146
G1 F2100
G1 X130.665 Y120.525 E.01055
; LINE_WIDTH: 0.689144
G1 X130.773 Y120.497 E.01101
; LINE_WIDTH: 0.73914
G1 X130.881 Y120.469 E.01192
; LINE_WIDTH: 0.789135
G1 X130.989 Y120.44 E.01283
; LINE_WIDTH: 0.839131
G1 X131.098 Y120.412 E.01374
; LINE_WIDTH: 0.899006
G1 X131.13 Y120.407 E.00431
G1 X131.255 Y120.175 E.03487
; LINE_WIDTH: 0.873372
G1 X131.348 Y120.013 E.02403
; LINE_WIDTH: 0.848276
G1 X131.403 Y119.91 E.01454
; LINE_WIDTH: 0.814405
G1 X131.494 Y119.75 E.02178
; LINE_WIDTH: 0.774113
G1 X131.552 Y119.644 E.0136
; LINE_WIDTH: 0.740575
G1 X131.867 Y119.092 E.06777
; LINE_WIDTH: 0.709151
G1 X132.183 Y118.541 E.06452
; WIPE_START
G1 F24000
G1 X131.867 Y119.092 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X133.995 Y125.491 Z.8 F30000
G1 Z.4
G1 E3 F1800
; LINE_WIDTH: 0.655891
G1 F2100
G1 X134.06 Y125.557 E.00867
; LINE_WIDTH: 0.676726
G1 X134.126 Y125.623 E.00898
; LINE_WIDTH: 0.718397
G1 X134.192 Y125.69 E.00962
; LINE_WIDTH: 0.760067
G1 X134.257 Y125.756 E.01025
; LINE_WIDTH: 0.801738
G1 X134.323 Y125.822 E.01088
; LINE_WIDTH: 0.843408
G1 X134.388 Y125.889 E.01152
; LINE_WIDTH: 0.899011
G1 X134.409 Y125.914 E.0043
G1 X134.672 Y125.907 E.03487
; LINE_WIDTH: 0.87337
G1 X134.859 Y125.906 E.02402
; LINE_WIDTH: 0.848282
G1 X134.976 Y125.902 E.01453
; LINE_WIDTH: 0.814408
G1 X135.16 Y125.901 E.02179
; LINE_WIDTH: 0.774107
G1 X135.281 Y125.898 E.0136
; LINE_WIDTH: 0.740934
G1 X135.916 Y125.896 E.0678
; LINE_WIDTH: 0.710243
G1 X136.551 Y125.893 E.06463
; WIPE_START
G1 F24000
G1 X135.916 Y125.896 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X133.446 Y128.556 Z.8 F30000
G1 Z.4
G1 E3 F1800
; LINE_WIDTH: 0.664147
G1 F2100
G1 X133.475 Y128.665 E.01055
; LINE_WIDTH: 0.689145
G1 X133.503 Y128.773 E.01101
; LINE_WIDTH: 0.739141
G1 X133.531 Y128.881 E.01192
; LINE_WIDTH: 0.789136
G1 X133.56 Y128.989 E.01283
; LINE_WIDTH: 0.839132
G1 X133.588 Y129.098 E.01374
; LINE_WIDTH: 0.899005
G1 X133.593 Y129.13 E.00431
G1 X133.825 Y129.255 E.03487
; LINE_WIDTH: 0.873373
G1 X133.987 Y129.348 E.02403
; LINE_WIDTH: 0.848277
G1 X134.09 Y129.403 E.01453
; LINE_WIDTH: 0.814407
G1 X134.25 Y129.494 E.02178
; LINE_WIDTH: 0.774119
G1 X134.356 Y129.552 E.0136
; LINE_WIDTH: 0.740583
G1 X134.908 Y129.867 E.06777
; LINE_WIDTH: 0.709152
G1 X135.459 Y130.183 E.06452
; WIPE_START
G1 F24000
G1 X134.908 Y129.867 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X131.439 Y130.937 Z.8 F30000
G1 Z.4
G1 E3 F1800
; LINE_WIDTH: 0.664175
G1 F2100
G1 X131.409 Y131.045 E.01055
; LINE_WIDTH: 0.689173
G1 X131.379 Y131.153 E.01101
; LINE_WIDTH: 0.73917
G1 X131.35 Y131.261 E.01192
; LINE_WIDTH: 0.789167
G1 X131.32 Y131.369 E.01283
; LINE_WIDTH: 0.839164
G1 X131.291 Y131.477 E.01374
; LINE_WIDTH: 0.899007
G1 X131.279 Y131.507 E.00431
G1 X131.417 Y131.731 E.03488
; LINE_WIDTH: 0.873374
G1 X131.511 Y131.893 E.02402
; LINE_WIDTH: 0.848283
G1 X131.573 Y131.993 E.01454
; LINE_WIDTH: 0.814412
G1 X131.665 Y132.151 E.02178
; LINE_WIDTH: 0.774118
G1 X131.729 Y132.254 E.01361
; LINE_WIDTH: 0.74057
G1 X132.048 Y132.803 E.06777
; LINE_WIDTH: 0.709135
G1 X132.368 Y133.352 E.06451
; WIPE_START
G1 F24000
G1 X132.048 Y132.803 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X128.509 Y131.995 Z.8 F30000
G1 Z.4
G1 E3 F1800
; LINE_WIDTH: 0.635052
G1 F2100
G1 X128.443 Y132.06 E.00835
; LINE_WIDTH: 0.676723
G1 X128.377 Y132.126 E.00898
; LINE_WIDTH: 0.718394
G1 X128.31 Y132.192 E.00962
; LINE_WIDTH: 0.760065
G1 X128.244 Y132.257 E.01025
; LINE_WIDTH: 0.801736
G1 X128.178 Y132.323 E.01088
; LINE_WIDTH: 0.843406
G1 X128.111 Y132.388 E.01152
; LINE_WIDTH: 0.89901
G1 X128.086 Y132.409 E.0043
G1 X128.093 Y132.672 E.03487
; LINE_WIDTH: 0.87337
G1 X128.094 Y132.859 E.02402
; LINE_WIDTH: 0.848282
G1 X128.098 Y132.976 E.01453
; LINE_WIDTH: 0.814408
G1 X128.099 Y133.16 E.02179
; LINE_WIDTH: 0.774107
G1 X128.102 Y133.281 E.0136
; LINE_WIDTH: 0.740934
G1 X128.104 Y133.916 E.0678
; LINE_WIDTH: 0.725588
G1 X128.107 Y134.551 E.06622
; WIPE_START
G1 F24000
G1 X128.104 Y133.916 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X125.444 Y131.446 Z.8 F30000
G1 Z.4
G1 E3 F1800
; LINE_WIDTH: 0.639177
G1 F2100
G1 X125.335 Y131.475 E.01009
; LINE_WIDTH: 0.689175
G1 X125.227 Y131.503 E.01101
; LINE_WIDTH: 0.739173
G1 X125.119 Y131.531 E.01192
; LINE_WIDTH: 0.789171
G1 X125.011 Y131.56 E.01283
; LINE_WIDTH: 0.839169
G1 X124.902 Y131.588 E.01374
; LINE_WIDTH: 0.899007
G1 X124.87 Y131.593 E.00431
G1 X124.745 Y131.825 E.03487
; LINE_WIDTH: 0.873371
G1 X124.652 Y131.987 E.02403
; LINE_WIDTH: 0.848279
G1 X124.597 Y132.09 E.01453
; LINE_WIDTH: 0.814408
G1 X124.506 Y132.25 E.02179
; LINE_WIDTH: 0.774121
G1 X124.448 Y132.356 E.0136
; LINE_WIDTH: 0.740585
G1 X124.133 Y132.908 E.06777
; LINE_WIDTH: 0.724869
G1 X123.817 Y133.459 E.06614
; WIPE_START
G1 F24000
G1 X124.133 Y132.908 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.063 Y129.439 Z.8 F30000
G1 Z.4
G1 E3 F1800
; LINE_WIDTH: 0.635072
G1 F2100
G1 X122.973 Y129.414 E.00835
; LINE_WIDTH: 0.676743
G1 X122.883 Y129.389 E.00898
; LINE_WIDTH: 0.718414
G1 X122.793 Y129.365 E.00962
; LINE_WIDTH: 0.760084
G1 X122.703 Y129.34 E.01025
; LINE_WIDTH: 0.801755
G1 X122.613 Y129.315 E.01088
; LINE_WIDTH: 0.843425
G1 X122.523 Y129.29 E.01152
; LINE_WIDTH: 0.899016
G1 X122.493 Y129.279 E.0043
G1 X122.269 Y129.417 E.03487
; LINE_WIDTH: 0.873376
G1 X122.107 Y129.511 E.02402
; LINE_WIDTH: 0.848283
G1 X122.007 Y129.573 E.01454
; LINE_WIDTH: 0.81441
G1 X121.849 Y129.665 E.02178
; LINE_WIDTH: 0.774119
G1 X121.746 Y129.729 E.0136
; LINE_WIDTH: 0.740576
M73 P59 R4
G1 X121.197 Y130.048 E.06777
; LINE_WIDTH: 0.724858
G1 X120.648 Y130.368 E.06614
; CHANGE_LAYER
; Z_HEIGHT: 0.8
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X121.197 Y130.048 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 2/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L2
M991 S0 P1 ;notify layer change
M106 S255
M106 P2 S178
; open powerlost recovery
M1003 S1
M204 S10000
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z.8 I.682 J1.008 P1  F30000
G1 X131.342 Y123.181 Z.8
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2451.784
G1 X131.444 Y123.276 E.01669
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X128.101 Y121.66 I-2.779 J-3.338 E2.00532
G3 X130.78 Y122.66 I-.12 J4.41 E.34845
G1 X131.254 Y123.099 E.07733
G1 X130.71 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06533
G3 X128.106 Y122.394 I-2.308 J-2.774 E1.6686
G3 X130.627 Y123.51 I-.171 J3.792 E.33755
M204 S10000
; WIPE_START
G1 F24000
G1 X130.661 Y125.51 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.078 Y126.382 Z1.2 F30000
G1 X122.165 Y126.487 Z1.2
G1 Z.8
G1 E3 F1800
; FEATURE: Inner wall
G1 F2451.784
G1 X121.642 Y126.47 E.06267
G1 X121.625 Y126.061 E.04899
G1 X122.248 Y125.989 E.07502
G3 X122.792 Y123.559 I15.35 J2.159 E.29835
G1 X122.259 Y123.228 E.07506
G1 X122.449 Y122.865 E.04899
G1 X123.024 Y123.115 E.07502
G3 X124.71 Y121.282 I12.213 J9.543 E.29836
G1 X124.414 Y120.729 E.07507
G1 X124.76 Y120.509 E.04899
G1 X125.133 Y121.013 E.07502
G3 X127.51 Y120.269 I5.806 J14.373 E.29836
G1 X127.53 Y119.642 E.07507
G1 X127.939 Y119.625 E.04899
G1 X128.011 Y120.248 E.07502
G3 X130.441 Y120.792 I-2.159 J15.35 E.29835
G1 X130.772 Y120.259 E.07507
G1 X131.135 Y120.448 E.04899
G1 X130.885 Y121.024 E.07502
G3 X132.718 Y122.71 I-9.543 J12.213 E.29836
G1 X133.271 Y122.414 E.07506
G1 X133.491 Y122.76 E.04899
G1 X132.987 Y123.133 E.07501
G3 X133.731 Y125.51 I-14.373 J5.806 E.29836
G1 X134.358 Y125.53 E.07507
G1 X134.375 Y125.939 E.04899
G1 X133.752 Y126.011 E.07502
G3 X133.208 Y128.441 I-15.351 J-2.159 E.29836
G1 X133.741 Y128.772 E.07506
G1 X133.551 Y129.135 E.04899
G1 X132.976 Y128.885 E.07501
G3 X131.29 Y130.718 I-12.214 J-9.544 E.29836
G1 X131.586 Y131.271 E.07506
G1 X131.24 Y131.491 E.04899
G1 X130.867 Y130.987 E.07501
G3 X128.49 Y131.731 I-5.806 J-14.373 E.29836
G1 X128.47 Y132.358 E.07506
G1 X128.061 Y132.375 E.04899
G1 X127.989 Y131.752 E.07502
G3 X125.559 Y131.208 I2.159 J-15.35 E.29835
G1 X125.228 Y131.741 E.07507
G1 X124.865 Y131.552 E.04899
G1 X125.115 Y130.976 E.07502
G3 X123.282 Y129.29 I9.544 J-12.214 E.29836
G1 X122.729 Y129.586 E.07506
G1 X122.509 Y129.24 E.04899
G1 X123.013 Y128.867 E.07502
G3 X122.272 Y126.506 I14.374 J-5.806 E.2964
G1 X121.698 Y127.206 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X121.624 Y127.204 E.0088
G3 X118.93 Y126.729 I-.049 J-7.608 E.32912
G3 X118.917 Y126.569 I1.83 J-.228 E.01925
G3 X118.901 Y126.027 I6.203 J-.456 E.06494
G3 X121.619 Y125.323 I3.264 J7.003 E.33784
G3 X121.939 Y123.894 I10.731 J1.651 E.17536
G1 X121.876 Y123.855 E.0088
G3 X119.78 Y122.097 I3.762 J-6.613 E.32912
G3 X119.849 Y121.951 I1.699 J.717 E.01925
G3 X120.106 Y121.475 I5.383 J2.593 E.06478
G3 X122.813 Y122.223 I-.657 J7.648 E.33788
G3 X123.804 Y121.145 I8.467 J6.794 E.17536
G1 X123.769 Y121.08 E.0088
G3 X122.833 Y118.51 I6.565 J-3.846 E.32912
G3 X122.966 Y118.418 I1.113 J1.471 E.01925
G3 X123.426 Y118.134 I3.365 J4.938 E.06478
G3 X125.396 Y120.135 I-4.393 J6.294 E.33788
G3 X126.794 Y119.698 I3.936 J10.119 E.17536
G1 X126.796 Y119.624 E.0088
G3 X127.271 Y116.93 I7.608 J-.049 E.32912
G3 X127.431 Y116.917 I.228 J1.83 E.01925
G3 X127.973 Y116.901 I.456 J6.204 E.06494
G3 X128.677 Y119.619 I-7.003 J3.264 E.33784
G3 X130.106 Y119.939 I-1.651 J10.731 E.17536
G1 X130.145 Y119.876 E.0088
G3 X131.903 Y117.78 I6.613 J3.762 E.32912
G3 X132.049 Y117.849 I-.718 J1.7 E.01925
G3 X132.525 Y118.106 I-2.594 J5.383 E.06478
G3 X131.777 Y120.813 I-7.648 J-.657 E.33788
G3 X132.855 Y121.804 I-6.794 J8.467 E.17536
G1 X132.92 Y121.769 E.0088
G3 X135.49 Y120.833 I3.846 J6.565 E.32912
G3 X135.582 Y120.966 I-1.471 J1.113 E.01925
G3 X135.866 Y121.426 I-4.938 J3.365 E.06478
G3 X133.865 Y123.396 I-6.294 J-4.393 E.33788
G3 X134.302 Y124.794 I-10.119 J3.936 E.17536
G1 X134.376 Y124.796 E.0088
G3 X137.07 Y125.271 I.048 J7.608 E.32912
G3 X137.083 Y125.431 I-1.83 J.228 E.01925
G3 X137.099 Y125.973 I-6.203 J.456 E.06494
G3 X134.381 Y126.677 I-3.264 J-7.003 E.33784
G3 X134.061 Y128.106 I-10.731 J-1.651 E.17536
G1 X134.124 Y128.145 E.0088
G3 X136.22 Y129.903 I-3.762 J6.613 E.32912
G3 X136.151 Y130.049 I-1.7 J-.718 E.01925
G3 X135.894 Y130.525 I-5.383 J-2.594 E.06478
G3 X133.188 Y129.777 I.657 J-7.647 E.33788
G3 X132.196 Y130.855 I-8.467 J-6.795 E.17536
G1 X132.231 Y130.92 E.0088
G3 X133.167 Y133.49 I-6.565 J3.846 E.32912
G3 X133.034 Y133.582 I-1.113 J-1.471 E.01925
G3 X132.574 Y133.866 I-3.365 J-4.939 E.06478
G3 X130.604 Y131.865 I4.393 J-6.294 E.33788
G3 X129.206 Y132.302 I-3.936 J-10.118 E.17536
G1 X129.204 Y132.376 E.0088
G3 X128.729 Y135.07 I-7.608 J.049 E.32912
G3 X128.569 Y135.083 I-.228 J-1.83 E.01925
G3 X128.027 Y135.099 I-.456 J-6.204 E.06494
G3 X127.323 Y132.381 I7.003 J-3.264 E.33784
G3 X125.894 Y132.061 I1.651 J-10.731 E.17536
G1 X125.855 Y132.124 E.0088
G3 X124.097 Y134.22 I-6.613 J-3.762 E.32912
G3 X123.951 Y134.151 I.717 J-1.699 E.01925
G3 X123.475 Y133.894 I2.594 J-5.383 E.06478
G3 X124.223 Y131.187 I7.648 J.657 E.33788
G3 X123.145 Y130.196 I6.795 J-8.468 E.17536
G1 X123.08 Y130.231 E.0088
G3 X120.51 Y131.167 I-3.846 J-6.565 E.32912
G3 X120.418 Y131.034 I1.471 J-1.113 E.01925
G3 X120.134 Y130.574 I4.938 J-3.365 E.06478
G3 X122.135 Y128.604 I6.294 J4.393 E.33788
G3 X121.726 Y127.323 I10.119 J-3.936 E.161
M204 S10000
; WIPE_START
G1 F24000
G1 X121.624 Y127.204 E-.22335
G1 X121.033 Y127.185 E-.8429
G1 X120.339 Y127.111 E-.9941
G1 X119.797 Y126.997 E-.78965
; WIPE_END
G1 E-.15 F1800
G1 X121.267 Y126.282 Z1.2 F30000
G1 Z.8
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 1.04669
G1 F1873.34
G1 X120.88 Y126.297 E.06064
; LINE_WIDTH: 0.99831
G1 F1972.669
G1 X120.493 Y126.313 E.05759
; LINE_WIDTH: 0.974118
G1 F2026.395
G1 X119.277 Y126.391 E.17642
G1 X121.265 Y126.256 F30000
; LINE_WIDTH: 0.839782
G1 F2387.455
G1 X119.276 Y126.384 E.24493
G1 X119.276 Y126.377 F30000
; LINE_WIDTH: 0.666819
G1 F3000
G1 X121.265 Y126.249 E.18874
G1 X122.043 Y122.848 F30000
; LINE_WIDTH: 0.666814
G1 F3000
G1 X120.256 Y121.964 E.18875
G1 X120.253 Y121.97 F30000
; LINE_WIDTH: 0.839774
G1 F2387.479
G1 X122.04 Y122.855 E.24493
G1 X122.028 Y122.877 F30000
; LINE_WIDTH: 1.0467
G1 F1873.32
G1 X121.685 Y122.697 E.06065
; LINE_WIDTH: 0.998314
G1 F1972.661
G1 X121.342 Y122.517 E.05759
; LINE_WIDTH: 0.974121
G1 F2026.387
G1 X120.25 Y121.977 E.17642
; WIPE_START
G1 F24000
G1 X121.342 Y122.517 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.3 Y118.641 Z1.2 F30000
G1 Z.8
M73 P60 R4
G1 E3 F1800
; LINE_WIDTH: 0.974106
G1 F2026.421
G1 X123.976 Y119.655 E.17641
; LINE_WIDTH: 0.998304
G1 F1972.683
G1 X124.182 Y119.982 E.05759
; LINE_WIDTH: 1.0467
G1 F1873.326
G1 X124.389 Y120.31 E.06065
G1 X124.411 Y120.296 F30000
; LINE_WIDTH: 0.839794
G1 F2387.416
G1 X123.306 Y118.637 E.24494
G1 X123.312 Y118.633 F30000
; LINE_WIDTH: 0.666812
G1 F3000
G1 X124.417 Y120.292 E.18874
; WIPE_START
G1 F24000
G1 X123.312 Y118.633 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X127.609 Y117.277 Z1.2 F30000
G1 Z.8
G1 E3 F1800
; LINE_WIDTH: 0.974115
G1 F2026.402
G1 X127.687 Y118.493 E.17641
; LINE_WIDTH: 0.998308
G1 F1972.673
G1 X127.703 Y118.88 E.05759
; LINE_WIDTH: 1.0467
G1 F1873.331
G1 X127.718 Y119.267 E.06065
G1 X127.744 Y119.266 F30000
; LINE_WIDTH: 0.839782
G1 F2387.452
G1 X127.616 Y117.276 E.24493
G1 X127.623 Y117.276 F30000
; LINE_WIDTH: 0.666819
G1 F3000
G1 X127.751 Y119.265 E.18875
G1 X131.152 Y120.043 F30000
; LINE_WIDTH: 0.650291
G1 F3000
G1 X132.036 Y118.256 E.18338
G1 X132.03 Y118.253 F30000
; LINE_WIDTH: 0.821466
G1 F2446.899
G1 X131.145 Y120.04 E.23898
G1 X130.659 Y119.744 F30000
; LINE_WIDTH: 1.06286
G1 F1842.331
G1 X131.352 Y119.592 E.11288
G1 X131.417 Y119.467 E.02245
; LINE_WIDTH: 0.998312
G1 F1972.664
G1 X131.483 Y119.342 E.02097
; LINE_WIDTH: 0.968858
G1 F2038.466
G1 X132.023 Y118.25 E.17537
; WIPE_START
G1 F24000
G1 X131.483 Y119.342 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X135.359 Y121.3 Z1.2 F30000
G1 Z.8
G1 E3 F1800
; LINE_WIDTH: 0.968848
G1 F2038.487
G1 X134.345 Y121.976 E.17536
; LINE_WIDTH: 0.998307
G1 F1972.675
G1 X134.226 Y122.051 E.02098
; LINE_WIDTH: 1.06288
G1 F1842.303
G1 X134.107 Y122.126 E.02246
G1 X133.431 Y121.912 E.11289
G1 X133.704 Y122.411 F30000
; LINE_WIDTH: 0.821475
G1 F2446.868
G1 X135.363 Y121.306 E.23899
G1 X135.367 Y121.312 F30000
; LINE_WIDTH: 0.650298
G1 F3000
G1 X133.708 Y122.417 E.18338
G1 X132.209 Y124.699 F30000
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.881683
G1 F2261.755
G1 X132.209 Y127.38 E.34768
G1 X132.637 Y127.618 E.06359
G1 X132.785 Y127.071 E.0735
G1 X132.999 Y125.878 E.1572
G1 X132.992 Y125.705 E.02244
G1 X132.668 Y124.505 E.16126
G1 X132.327 Y124.723 E.05256
G1 X132.519 Y123.685 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 0.720496
G1 F2836.186
G1 X132.261 Y123.297 E.04819
; LINE_WIDTH: 0.670688
G1 F3000
G1 X132.003 Y122.909 E.04441
G2 X131.191 Y122.141 I-10.15 J9.917 E.10654
; LINE_WIDTH: 0.6894
G1 F2982.307
G2 X130.765 Y121.806 I-6.415 J7.714 E.05329
; LINE_WIDTH: 0.727269
G1 F2806.236
G1 X130.557 Y121.659 E.02665
; LINE_WIDTH: 0.771303
G1 F2625.964
G1 X130.314 Y121.498 E.03261
; LINE_WIDTH: 0.76246
G1 F2660.283
G1 X130.074 Y121.412 E.0281
; LINE_WIDTH: 0.719974
G1 F2838.519
G2 X129.803 Y121.315 I-1.934 J4.988 E.02977
; LINE_WIDTH: 0.686268
G1 F2997.863
G2 X128.219 Y120.977 I-2.289 J6.837 E.15875
; LINE_WIDTH: 0.735365
G1 F2771.261
G1 X128.004 Y120.959 E.02285
; LINE_WIDTH: 0.775962
G1 F2608.239
G2 X127.674 Y120.957 I-.169 J.836 E.03733
; LINE_WIDTH: 0.748671
G1 F2715.628
G1 X127.424 Y121.004 E.02751
; LINE_WIDTH: 0.710473
G1 F2881.697
G2 X127.142 Y121.058 I.858 J5.265 E.02927
; LINE_WIDTH: 0.686741
G1 F2995.507
G2 X125.637 Y121.558 I1.509 J7.049 E.15557
; LINE_WIDTH: 0.724417
G1 F2818.77
G1 X125.606 Y121.572 E.00359
; LINE_WIDTH: 0.744043
G1 F2734.723
G1 X125.447 Y121.649 E.01889
; LINE_WIDTH: 0.775602
G1 F2609.599
G2 X125.136 Y121.846 I.469 J1.087 E.04162
; LINE_WIDTH: 0.736125
G1 F2768.019
G1 X124.944 Y122.013 E.02698
; LINE_WIDTH: 0.684832
G1 F3000
G2 X123.919 Y123.09 I3.947 J4.78 E.1455
; LINE_WIDTH: 0.715464
G1 F2858.855
G2 X123.667 Y123.427 I6.103 J4.831 E.04319
; LINE_WIDTH: 0.753368
G1 F2696.52
G1 X123.591 Y123.54 E.01484
; LINE_WIDTH: 0.774761
G1 F2612.783
G2 X123.427 Y123.875 I.687 J.543 E.04217
; LINE_WIDTH: 0.741742
G1 F2744.315
G1 X123.415 Y123.909 E.00379
; LINE_WIDTH: 0.724844
G1 F2816.889
G1 X123.334 Y124.15 E.0265
; LINE_WIDTH: 0.683126
G1 F3000
G2 X123.014 Y125.476 I5.757 J2.09 E.1331
; LINE_WIDTH: 0.700842
G1 F2926.825
G1 X122.986 Y125.729 E.02551
; LINE_WIDTH: 0.733348
G1 F2779.89
G2 X122.954 Y126.018 I5.319 J.734 E.03065
; LINE_WIDTH: 0.767914
G1 F2639.013
G2 X122.991 Y126.525 I1.182 J.167 E.05693
; LINE_WIDTH: 0.729383
G1 F2797.017
G1 X122.998 Y126.559 E.00365
; LINE_WIDTH: 0.69171
G1 F2970.939
G2 X123.223 Y127.495 I9.567 J-1.807 E.09513
; LINE_WIDTH: 0.681405
G1 F3000
G1 X123.258 Y127.607 E.01136
G2 X123.45 Y128.112 I41.768 J-15.64 E.05249
; LINE_WIDTH: 0.708836
G1 F2889.268
G1 X123.554 Y128.345 E.02585
; LINE_WIDTH: 0.745678
G1 F2727.944
G2 X123.673 Y128.611 I4.976 J-2.071 E.03133
; LINE_WIDTH: 0.781914
G1 F2585.936
G2 X123.731 Y128.72 I.291 J-.085 E.01413
; LINE_WIDTH: 0.774581
G1 F2613.465
G1 X123.854 Y128.87 E.02171
; LINE_WIDTH: 0.735507
G1 F2770.652
G2 X123.999 Y129.045 I3.328 J-2.602 E.0241
; LINE_WIDTH: 0.686261
G1 F2997.9
G2 X125.179 Y130.152 I5.32 J-4.49 E.15869
; LINE_WIDTH: 0.718084
G1 F2847.003
G1 X125.386 Y130.3 E.02625
; LINE_WIDTH: 0.759287
G1 F2672.818
G2 X125.624 Y130.469 I3.249 J-4.319 E.03209
; LINE_WIDTH: 0.787433
G1 F2565.594
G1 X125.653 Y130.487 E.00382
; LINE_WIDTH: 0.771399
G1 F2625.596
G1 X125.876 Y130.57 E.02663
; LINE_WIDTH: 0.727965
G1 F2803.194
G2 X126.132 Y130.663 I1.857 J-4.697 E.02846
; LINE_WIDTH: 0.685877
G1 F2999.819
G2 X127.711 Y131.016 I2.332 J-6.735 E.15861
; LINE_WIDTH: 0.728247
G1 F2801.966
G1 X127.961 Y131.038 E.02626
; LINE_WIDTH: 0.772241
G1 F2622.378
G1 X128.257 Y131.054 E.0331
; LINE_WIDTH: 0.760761
G1 F2666.982
G1 X128.507 Y131.009 E.02803
; LINE_WIDTH: 0.718785
G1 F2843.853
G2 X128.791 Y130.957 I-.825 J-5.288 E.02971
; LINE_WIDTH: 0.686372
G1 F2997.347
G2 X130.33 Y130.456 I-1.446 J-7.07 E.15879
; LINE_WIDTH: 0.736357
G1 F2767.034
G1 X130.521 Y130.366 E.02238
; LINE_WIDTH: 0.776133
G1 F2607.592
G2 X130.811 Y130.199 I-.291 J-.837 E.03785
; LINE_WIDTH: 0.747113
G1 F2722.027
G1 X131.004 Y130.033 E.02745
; LINE_WIDTH: 0.709426
G1 F2886.536
G2 X131.221 Y129.845 I-3.38 J-4.128 E.02921
; LINE_WIDTH: 0.675505
G1 F3000
G2 X131.804 Y129.275 I-11.52 J-12.38 E.07836
; LINE_WIDTH: 0.623852
G1 X131.991 Y129.078 E.02379
G1 X132.417 Y128.38 E.0717
G1 X133.957 Y129.152 F30000
; LINE_WIDTH: 0.650289
G1 F3000
G1 X135.744 Y130.036 E.18338
G1 X135.747 Y130.03 F30000
; LINE_WIDTH: 0.821457
G1 F2446.927
G1 X133.96 Y129.145 E.23899
G1 X134.256 Y128.659 F30000
; LINE_WIDTH: 1.06288
G1 F1842.304
G1 X134.408 Y129.352 E.11288
G1 X134.533 Y129.417 E.02246
; LINE_WIDTH: 0.998319
G1 F1972.649
G1 X134.658 Y129.483 E.02097
; LINE_WIDTH: 0.968866
G1 F2038.448
G1 X135.75 Y130.023 E.17537
; WIPE_START
G1 F24000
G1 X134.658 Y129.483 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X134.735 Y125.751 Z1.2 F30000
G1 Z.8
G1 E3 F1800
; LINE_WIDTH: 0.650302
G1 F3000
G1 X136.724 Y125.623 E.18338
G1 X136.724 Y125.616 F30000
; LINE_WIDTH: 0.821477
G1 F2446.861
G1 X134.735 Y125.744 E.23898
G1 X134.748 Y125.175 F30000
; LINE_WIDTH: 1.06286
G1 F1842.343
G1 X135.226 Y125.699 E.11289
G1 X135.366 Y125.693 E.02245
; LINE_WIDTH: 0.998301
G1 F1972.688
G1 X135.507 Y125.687 E.02097
; LINE_WIDTH: 0.968858
G1 F2038.466
G1 X136.723 Y125.609 E.17537
; WIPE_START
G1 F24000
G1 X135.507 Y125.687 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X132.885 Y132.855 Z1.2 F30000
G1 X132.7 Y133.359 Z1.2
G1 Z.8
G1 E3 F1800
; LINE_WIDTH: 0.968856
G1 F2038.47
G1 X132.024 Y132.345 E.17537
; LINE_WIDTH: 0.998306
G1 F1972.677
G1 X131.949 Y132.226 E.02098
; LINE_WIDTH: 1.06287
G1 F1842.315
G1 X131.874 Y132.107 E.02246
G1 X132.088 Y131.431 E.11288
G1 X131.589 Y131.704 F30000
; LINE_WIDTH: 0.821473
G1 F2446.874
G1 X132.694 Y133.363 E.23899
G1 X132.688 Y133.367 F30000
; LINE_WIDTH: 0.650298
G1 F3000
G1 X131.583 Y131.708 E.18338
G1 X128.249 Y132.735 F30000
; LINE_WIDTH: 0.666808
G1 F3000
G1 X128.377 Y134.724 E.18874
G1 X128.384 Y134.724 F30000
; LINE_WIDTH: 0.839796
G1 F2387.409
G1 X128.256 Y132.734 E.24494
G1 X128.282 Y132.733 F30000
; LINE_WIDTH: 1.0467
G1 F1873.329
G1 X128.297 Y133.12 E.06065
; LINE_WIDTH: 0.998302
G1 F1972.686
G1 X128.313 Y133.507 E.05759
; LINE_WIDTH: 0.974106
G1 F2026.421
G1 X128.391 Y134.723 E.17641
; WIPE_START
G1 F24000
G1 X128.313 Y133.507 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.977 Y133.75 Z1.2 F30000
G1 Z.8
G1 E3 F1800
; LINE_WIDTH: 0.974119
G1 F2026.392
G1 X124.517 Y132.658 E.17642
; LINE_WIDTH: 0.99831
G1 F1972.668
G1 X124.697 Y132.315 E.05759
; LINE_WIDTH: 1.04669
G1 F1873.338
G1 X124.877 Y131.972 E.06064
G1 X124.855 Y131.96 F30000
; LINE_WIDTH: 0.839771
G1 F2387.488
G1 X123.97 Y133.747 E.24493
G1 X123.964 Y133.744 F30000
; LINE_WIDTH: 0.666817
G1 F3000
G1 X124.848 Y131.957 E.18874
G1 X122.292 Y129.583 F30000
; LINE_WIDTH: 0.666819
G1 F3000
G1 X120.633 Y130.688 E.18875
G1 X120.637 Y130.694 F30000
; LINE_WIDTH: 0.839795
G1 F2387.414
G1 X122.296 Y129.589 E.24494
G1 X122.31 Y129.611 F30000
; LINE_WIDTH: 1.0467
G1 F1873.327
G1 X121.982 Y129.818 E.06065
; LINE_WIDTH: 0.998304
G1 F1972.683
G1 X121.655 Y130.024 E.05759
; LINE_WIDTH: 0.974107
G1 F2026.419
G1 X120.641 Y130.7 E.17641
; CHANGE_LAYER
; Z_HEIGHT: 1.2
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X121.655 Y130.024 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 3/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L3
M991 S0 P2 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z1.2 I.702 J.994 P1  F30000
G1 X131.342 Y123.181 Z1.2
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2407
G1 X131.444 Y123.276 E.01666
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X128.074 Y121.66 I-2.777 J-3.339 E2.0011
G3 X130.78 Y122.66 I-.088 J4.402 E.35174
G1 X131.254 Y123.1 E.07736
G1 X130.71 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2407
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X128.079 Y122.394 I-2.307 J-2.774 E1.66468
G3 X130.627 Y123.51 I-.14 J3.787 E.34081
M204 S10000
; WIPE_START
G1 F24000
G1 X130.661 Y125.51 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.095 Y126.513 Z1.6 F30000
G1 X122.183 Y126.634 Z1.6
G1 Z1.2
G1 E3 F1800
; FEATURE: Inner wall
G1 F2407
G1 X121.733 Y126.641 E.05379
G1 X121.701 Y126.228 E.04948
G1 X122.261 Y126.149 E.06763
G3 X122.735 Y123.691 I13.385 J1.31 E.29999
G1 X122.252 Y123.421 E.06615
G1 X122.431 Y123.048 E.04948
G1 X122.955 Y123.259 E.06763
G3 X124.595 Y121.368 I10.937 J7.827 E.29999
G1 X124.312 Y120.893 E.06615
G1 X124.653 Y120.659 E.04948
G1 X125.001 Y121.104 E.06763
G3 X127.368 Y120.286 I5.558 J12.248 E.29999
G1 X127.359 Y119.733 E.06615
G1 X127.772 Y119.701 E.04948
G1 X127.851 Y120.261 E.06763
G3 X130.309 Y120.735 I-1.31 J13.385 E.29999
G1 X130.579 Y120.252 E.06615
G1 X130.952 Y120.431 E.04948
G1 X130.741 Y120.955 E.06763
G3 X132.632 Y122.595 I-7.827 J10.937 E.29999
G1 X133.107 Y122.312 E.06615
G1 X133.341 Y122.653 E.04948
G1 X132.896 Y123.001 E.06763
G3 X133.714 Y125.368 I-12.248 J5.558 E.29999
G1 X134.267 Y125.359 E.06615
G1 X134.299 Y125.772 E.04948
G1 X133.739 Y125.851 E.06763
G3 X133.265 Y128.309 I-13.385 J-1.31 E.29999
G1 X133.748 Y128.579 E.06616
G1 X133.569 Y128.952 E.04948
G1 X133.045 Y128.741 E.06764
G3 X131.405 Y130.632 I-10.936 J-7.827 E.29999
G1 X131.688 Y131.107 E.06615
G1 X131.347 Y131.341 E.04948
G1 X130.999 Y130.896 E.06763
G3 X128.632 Y131.714 I-5.558 J-12.248 E.29999
G1 X128.641 Y132.267 E.06615
G1 X128.228 Y132.299 E.04948
G1 X128.149 Y131.739 E.06763
G3 X125.691 Y131.265 I1.31 J-13.384 E.29999
G1 X125.421 Y131.748 E.06615
M73 P61 R4
G1 X125.048 Y131.569 E.04948
G1 X125.259 Y131.045 E.06763
G3 X123.368 Y129.405 I7.827 J-10.936 E.29999
G1 X122.893 Y129.688 E.06615
G1 X122.659 Y129.347 E.04948
G1 X123.104 Y128.999 E.06763
G3 X122.29 Y126.649 I12.248 J-5.558 E.29799
G1 X121.735 Y127.375 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2407
G1 X121.658 Y127.376 E.00916
G3 X118.952 Y126.98 I-.34 J-7.124 E.32933
G1 X118.938 Y126.82 E.01925
G3 X118.904 Y126.281 I6.15 J-.651 E.06459
G3 X121.607 Y125.5 I3.353 J6.537 E.33873
G3 X121.887 Y124.058 I9.5 J1.093 E.17593
G1 X121.82 Y124.021 E.00916
G3 X119.674 Y122.325 I3.268 J-6.34 E.32933
G1 X119.742 Y122.179 E.01925
G3 X119.983 Y121.694 I5.666 J2.519 E.06474
G3 X122.714 Y122.371 I-.459 J7.705 E.33849
G3 X123.677 Y121.262 I7.681 J5.697 E.17593
G1 X123.638 Y121.196 E.00916
G3 X122.627 Y118.654 I6 J-3.857 E.32933
G1 X122.759 Y118.562 E.01925
G3 X123.21 Y118.263 I3.648 J5.014 E.06474
G3 X125.237 Y120.214 I-4.25 J6.443 E.33849
G3 X126.625 Y119.735 I3.804 J8.775 E.17593
G1 X126.624 Y119.658 E.00916
G3 X127.02 Y116.952 I7.124 J-.34 E.32933
G1 X127.18 Y116.938 E.01925
G3 X127.72 Y116.904 I.652 J6.166 E.06474
G3 X128.5 Y119.607 I-6.902 J3.455 E.33849
G3 X129.942 Y119.887 I-1.093 J9.501 E.17593
G1 X129.979 Y119.82 E.00916
G3 X131.675 Y117.674 I6.34 J3.268 E.32933
G1 X131.821 Y117.742 E.01925
G3 X132.306 Y117.983 I-2.519 J5.666 E.06474
G3 X131.629 Y120.714 I-7.705 J-.459 E.33849
G3 X132.738 Y121.677 I-5.697 J7.681 E.17593
G1 X132.804 Y121.638 E.00916
G3 X135.346 Y120.627 I3.857 J6 E.32933
G1 X135.438 Y120.759 E.01925
G3 X135.737 Y121.21 I-5.014 J3.648 E.06474
G3 X133.786 Y123.237 I-6.443 J-4.25 E.33849
G3 X134.265 Y124.625 I-8.775 J3.804 E.17593
G1 X134.342 Y124.624 E.00916
G3 X137.048 Y125.02 I.34 J7.124 E.32933
G1 X137.062 Y125.18 E.01925
G3 X137.096 Y125.719 I-6.15 J.651 E.06459
G3 X134.393 Y126.5 I-3.353 J-6.537 E.33873
G3 X134.113 Y127.942 I-9.5 J-1.093 E.17593
G1 X134.18 Y127.979 E.00916
G3 X136.326 Y129.675 I-3.268 J6.34 E.32933
G1 X136.258 Y129.821 E.01925
G3 X136.017 Y130.306 I-5.666 J-2.519 E.06474
G3 X133.286 Y129.629 I.459 J-7.704 E.33849
G3 X132.323 Y130.738 I-7.681 J-5.697 E.17593
G1 X132.362 Y130.804 E.00916
G3 X133.373 Y133.346 I-6 J3.857 E.32933
G1 X133.241 Y133.438 E.01925
G3 X132.79 Y133.737 I-3.647 J-5.014 E.06474
G3 X130.763 Y131.786 I4.25 J-6.443 E.33849
G3 X129.375 Y132.265 I-3.804 J-8.775 E.17593
G1 X129.376 Y132.342 E.00916
G3 X128.98 Y135.048 I-7.124 J.34 E.32933
G1 X128.82 Y135.062 E.01925
G3 X128.281 Y135.096 I-.651 J-6.151 E.06459
G3 X127.5 Y132.393 I6.537 J-3.353 E.33873
G3 X126.058 Y132.113 I1.093 J-9.5 E.17593
G1 X126.021 Y132.18 E.00916
G3 X124.325 Y134.326 I-6.34 J-3.268 E.32933
G1 X124.179 Y134.258 E.01925
G3 X123.694 Y134.017 I2.519 J-5.667 E.06474
G3 X124.371 Y131.286 I7.705 J.459 E.33849
G3 X123.262 Y130.323 I5.697 J-7.681 E.17593
G1 X123.196 Y130.362 E.00916
G3 X120.654 Y131.373 I-3.857 J-6 E.32933
G1 X120.562 Y131.241 E.01925
G3 X120.263 Y130.79 I5.014 J-3.648 E.06474
G3 X122.214 Y128.763 I6.443 J4.25 E.33849
G3 X121.766 Y127.491 I8.775 J-3.804 E.16157
M204 S10000
; WIPE_START
G1 F24000
G1 X121.658 Y127.376 E-.22412
G1 X121.071 Y127.378 E-.83664
G1 X120.373 Y127.323 E-.99774
G1 X119.827 Y127.224 E-.7915
; WIPE_END
G1 E-.15 F1800
G1 X121.351 Y126.457 Z1.6 F30000
G1 Z1.2
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 1.07889
G1 F1812.59
G1 X120.788 Y126.503 E.09127
; LINE_WIDTH: 1.04794
G1 F1870.9
G1 X120.648 Y126.51 E.02207
; LINE_WIDTH: 1.00127
G1 F1966.284
G1 X120.512 Y126.52 E.02035
; LINE_WIDTH: 0.977054
G1 F2019.719
G1 X119.291 Y126.633 E.1781
G1 X119.29 Y126.626 F30000
; LINE_WIDTH: 0.839743
G1 F2387.577
G1 X121.349 Y126.436 E.254
G1 X122.01 Y123.076 F30000
; LINE_WIDTH: 1.08225
G1 F1806.482
G2 X121.504 Y122.829 I-5.308 J10.222 E.09157
; LINE_WIDTH: 1.04738
G1 F1871.991
G1 X121.376 Y122.766 E.02232
; LINE_WIDTH: 0.998511
G1 F1972.236
G1 X121.248 Y122.703 E.02119
; LINE_WIDTH: 0.974074
G1 F2026.495
G1 X120.141 Y122.194 E.1764
G1 X120.144 Y122.187 F30000
; LINE_WIDTH: 0.839758
G1 F2387.529
G1 X122.022 Y123.052 E.25401
G1 X124.275 Y120.473 F30000
; LINE_WIDTH: 1.08225
G1 F1806.494
G2 X123.96 Y120.006 I-9.693 J6.189 E.09157
; LINE_WIDTH: 1.04738
G1 F1872
G1 X123.88 Y119.887 E.02232
; LINE_WIDTH: 0.998511
G1 F1972.234
G1 X123.801 Y119.769 E.02118
; LINE_WIDTH: 0.974078
G1 F2026.486
G1 X123.097 Y118.774 E.1764
G1 X123.103 Y118.77 F30000
; LINE_WIDTH: 0.839746
G1 F2387.569
G1 X124.297 Y120.458 E.254
M73 P61 R3
G1 X127.537 Y119.351 F30000
; LINE_WIDTH: 1.08225
G1 F1806.488
G2 X127.498 Y118.789 I-11.472 J.512 E.09157
; LINE_WIDTH: 1.04739
G1 F1871.988
G1 X127.489 Y118.646 E.02232
; LINE_WIDTH: 0.998517
G1 F1972.221
G1 X127.479 Y118.504 E.02118
; LINE_WIDTH: 0.974083
G1 F2026.475
G1 X127.367 Y117.291 E.17641
G1 X127.374 Y117.29 F30000
; LINE_WIDTH: 0.839731
G1 F2387.615
G1 X127.564 Y119.349 E.254
G1 X130.924 Y120.01 F30000
; LINE_WIDTH: 1.07682
G1 F1816.394
G2 X131.171 Y119.504 I-10.197 J-5.296 E.09107
; LINE_WIDTH: 1.04738
G1 F1871.99
G1 X131.234 Y119.376 E.02232
; LINE_WIDTH: 0.998512
G1 F1972.233
G1 X131.297 Y119.248 E.02119
; LINE_WIDTH: 0.968825
G1 F2038.542
G1 X131.807 Y118.14 E.17551
G1 X131.813 Y118.143 F30000
; LINE_WIDTH: 0.821422
G1 F2407
G1 X130.948 Y120.022 E.24796
G1 X133.527 Y122.275 F30000
; LINE_WIDTH: 1.07681
G1 F1816.403
G2 X133.994 Y121.96 I-6.194 J-9.702 E.09107
; LINE_WIDTH: 1.04738
G1 F1871.993
G1 X134.113 Y121.88 E.02232
; LINE_WIDTH: 0.998518
G1 F1972.22
G1 X134.231 Y121.801 E.02118
; LINE_WIDTH: 0.968828
G1 F2038.533
G1 X135.227 Y121.097 E.17551
G1 X135.231 Y121.103 F30000
; LINE_WIDTH: 0.821425
G1 F2407
G1 X133.542 Y122.297 E.24796
G1 X134.651 Y125.564 F30000
; LINE_WIDTH: 0.821431
G1 F2407
G1 X136.71 Y125.374 E.24783
G1 X136.709 Y125.367 F30000
; LINE_WIDTH: 0.970307
G1 F2035.125
G1 X135.488 Y125.48 E.17675
; LINE_WIDTH: 1.00128
G1 F1966.276
G1 X135.352 Y125.49 E.02035
; LINE_WIDTH: 1.04795
G1 F1870.889
G1 X135.212 Y125.497 E.02207
; LINE_WIDTH: 1.0704
G1 F1828.237
G1 X134.649 Y125.543 E.09049
G1 X132.205 Y125.669 F30000
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.852119
G1 F2349.015
G1 X132.184 Y126.275 E.0758
; LINE_WIDTH: 0.792682
G1 F2407
G2 X132.162 Y127.474 I16.925 J.903 E.13812
G1 X132.659 Y127.764 E.06627
G1 X132.861 Y126.931 E.09873
; LINE_WIDTH: 0.809194
G1 X132.925 Y126.328 E.07155
; LINE_WIDTH: 0.865986
G1 F2307.262
G1 X132.989 Y125.724 E.07717
G1 X132.977 Y125.558 E.02113
G1 X132.648 Y124.431 E.14936
G1 X132.205 Y124.518 E.0574
G1 X132.205 Y125.549 E.13104
G1 X132.285 Y123.727 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 0.863188
G1 F2315.569
G1 X132.23 Y123.448 E.03594
; LINE_WIDTH: 0.830229
G1 F2407
G1 X132.175 Y123.17 E.03441
; LINE_WIDTH: 0.790721
G1 X132.152 Y123.116 E.00677
; LINE_WIDTH: 0.750376
G1 X132.104 Y123.045 E.00925
; LINE_WIDTH: 0.715743
G1 X132.056 Y122.975 E.00877
; LINE_WIDTH: 0.676348
G1 X132.008 Y122.904 E.00822
G2 X130.761 Y121.814 I-7.354 J7.159 E.15956
; LINE_WIDTH: 0.70365
G1 X130.55 Y121.672 E.02563
; LINE_WIDTH: 0.737949
G2 X130.308 Y121.51 I-3.118 J4.379 E.0309
; LINE_WIDTH: 0.755278
G1 X130.207 Y121.449 E.01289
G1 X129.837 Y121.32 E.04281
; LINE_WIDTH: 0.684904
G2 X128.219 Y120.988 I-2.194 J6.578 E.16157
; LINE_WIDTH: 0.712164
G1 X127.965 Y120.971 E.026
; LINE_WIDTH: 0.750811
G2 X127.674 Y120.954 I-.47 J5.373 E.03162
; LINE_WIDTH: 0.778008
G1 X127.636 Y120.953 E.00433
; LINE_WIDTH: 0.763464
G1 X127.404 Y121 E.02604
; LINE_WIDTH: 0.722231
G2 X127.141 Y121.053 I.861 J4.924 E.02792
; LINE_WIDTH: 0.683923
G2 X125.612 Y121.583 I1.435 J6.608 E.15805
; LINE_WIDTH: 0.721781
G1 X125.387 Y121.697 E.02622
; LINE_WIDTH: 0.763562
G1 X125.129 Y121.838 E.03239
; LINE_WIDTH: 0.753805
G1 X124.939 Y122.007 E.02773
; LINE_WIDTH: 0.713735
G2 X124.725 Y122.199 I3.457 J4.069 E.02944
; LINE_WIDTH: 0.684341
G2 X123.679 Y123.434 I4.664 J5.012 E.1582
; LINE_WIDTH: 0.729361
G1 X123.564 Y123.613 E.02237
; LINE_WIDTH: 0.767631
G2 X123.406 Y123.905 I.701 J.566 E.03708
; LINE_WIDTH: 0.740719
G1 X123.328 Y124.148 E.02718
; LINE_WIDTH: 0.689803
G2 X123.112 Y124.913 I13.558 J4.239 E.07827
; LINE_WIDTH: 0.687551
G1 X123.106 Y124.944 E.00311
G2 X122.969 Y126.017 I8.407 J1.613 E.10617
; LINE_WIDTH: 0.737578
G1 X122.962 Y126.191 E.01845
; LINE_WIDTH: 0.767074
G2 X122.989 Y126.56 I1.248 J.095 E.04131
; LINE_WIDTH: 0.728893
G1 X123.045 Y126.809 E.02667
; LINE_WIDTH: 0.682801
G2 X123.456 Y128.109 I5.823 J-1.126 E.133
; LINE_WIDTH: 0.703206
G1 X123.672 Y128.57 E.05118
; LINE_WIDTH: 0.73021
G1 X123.687 Y128.601 E.00366
; LINE_WIDTH: 0.746444
G1 X123.75 Y128.719 E.01442
; LINE_WIDTH: 0.766129
G2 X123.97 Y129.024 I.836 J-.371 E.04188
; LINE_WIDTH: 0.73389
G1 X123.993 Y129.05 E.0037
; LINE_WIDTH: 0.718302
G1 X124.167 Y129.236 E.02622
; LINE_WIDTH: 0.68151
G2 X125.183 Y130.145 I4.4 J-3.895 E.1327
; LINE_WIDTH: 0.697179
G1 X125.393 Y130.289 E.02535
; LINE_WIDTH: 0.727664
G2 X125.632 Y130.453 I3.143 J-4.349 E.03033
; LINE_WIDTH: 0.759633
G2 X126.097 Y130.659 I.724 J-1.006 E.05621
; LINE_WIDTH: 0.690201
G2 X127.042 Y130.913 I2.563 J-7.653 E.09648
; LINE_WIDTH: 0.680194
G1 X127.175 Y130.939 E.0131
G2 X127.711 Y131.006 I4.879 J-36.692 E.05236
; LINE_WIDTH: 0.704594
G1 X127.965 Y131.024 E.02567
; LINE_WIDTH: 0.739406
G2 X128.256 Y131.043 I.506 J-5.361 E.03099
; LINE_WIDTH: 0.754464
G1 X128.364 Y131.045 E.01185
G1 X128.759 Y130.969 E.04378
; LINE_WIDTH: 0.684793
G2 X130.325 Y130.447 I-1.4 J-6.799 E.16153
; LINE_WIDTH: 0.713259
G1 X130.553 Y130.333 E.02605
; LINE_WIDTH: 0.752424
G2 X130.814 Y130.203 I-2.286 J-4.89 E.03171
; LINE_WIDTH: 0.778751
G1 X130.839 Y130.188 E.00326
; LINE_WIDTH: 0.762892
G1 X131.019 Y130.03 E.02654
; LINE_WIDTH: 0.721369
G2 X131.225 Y129.848 I-3.268 J-3.899 E.02836
; LINE_WIDTH: 0.678931
G2 X131.786 Y129.294 I-15.037 J-15.797 E.0762
; LINE_WIDTH: 0.633116
G2 X131.99 Y129.077 I-5.146 J-5.031 E.02664
; LINE_WIDTH: 0.625306
G1 X132.18 Y128.752 E.03308
; LINE_WIDTH: 0.639604
G1 X132.37 Y128.427 E.03396
G1 X133.978 Y128.948 F30000
; LINE_WIDTH: 0.821435
G1 F2407
G1 X135.856 Y129.813 E.24783
G1 X135.859 Y129.806 F30000
; LINE_WIDTH: 0.968823
M73 P62 R3
G1 F2038.546
G1 X134.752 Y129.297 E.17536
; LINE_WIDTH: 0.998509
G1 F1972.238
G1 X134.624 Y129.234 E.02118
; LINE_WIDTH: 1.04738
G1 F1872.005
G1 X134.496 Y129.171 E.02232
; LINE_WIDTH: 1.07681
G1 F1816.401
G3 X133.99 Y128.924 I4.789 J-10.444 E.09107
G1 X131.725 Y131.527 F30000
; LINE_WIDTH: 1.07681
G1 F1816.405
G2 X132.04 Y131.994 I9.682 J-6.181 E.09107
; LINE_WIDTH: 1.04738
G1 F1871.994
G1 X132.12 Y132.113 E.02232
; LINE_WIDTH: 0.998516
G1 F1972.224
G1 X132.199 Y132.231 E.02118
; LINE_WIDTH: 0.968828
G1 F2038.534
G1 X132.903 Y133.226 E.17536
G1 X132.897 Y133.23 F30000
; LINE_WIDTH: 0.821416
G1 F2407
G1 X131.703 Y131.542 E.24783
G1 X128.457 Y132.649 F30000
; LINE_WIDTH: 1.07889
G1 F1812.593
G1 X128.503 Y133.212 E.09127
; LINE_WIDTH: 1.04795
G1 F1870.891
G1 X128.51 Y133.352 E.02207
; LINE_WIDTH: 1.00128
G1 F1966.275
G1 X128.52 Y133.488 E.02035
; LINE_WIDTH: 0.977053
G1 F2019.721
G1 X128.633 Y134.709 E.1781
G1 X128.626 Y134.71 F30000
; LINE_WIDTH: 0.839747
G1 F2387.563
G1 X128.436 Y132.651 E.254
G1 X125.076 Y131.99 F30000
; LINE_WIDTH: 1.08225
G1 F1806.493
G2 X124.829 Y132.496 I10.198 J5.296 E.09157
; LINE_WIDTH: 1.04738
G1 F1872.008
G1 X124.766 Y132.624 E.02232
; LINE_WIDTH: 0.998505
G1 F1972.249
G1 X124.703 Y132.752 E.02118
; LINE_WIDTH: 0.974071
G1 F2026.502
G1 X124.194 Y133.859 E.1764
G1 X124.187 Y133.856 F30000
; LINE_WIDTH: 0.839759
G1 F2387.526
G1 X125.052 Y131.978 E.254
G1 X122.473 Y129.725 F30000
; LINE_WIDTH: 1.08225
G1 F1806.492
G2 X122.006 Y130.04 I6.187 J9.691 E.09157
; LINE_WIDTH: 1.04738
G1 F1871.994
G1 X121.887 Y130.12 E.02232
; LINE_WIDTH: 0.998521
G1 F1972.214
G1 X121.769 Y130.199 E.02118
; LINE_WIDTH: 0.974088
G1 F2026.463
G1 X120.774 Y130.903 E.17641
G1 X120.77 Y130.897 F30000
; LINE_WIDTH: 0.839734
G1 F2387.606
G1 X122.458 Y129.703 E.254
; CHANGE_LAYER
; Z_HEIGHT: 1.6
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X120.825 Y130.858 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 4/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L4
M991 S0 P3 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z1.6 I.717 J.983 P1  F30000
G1 X131.342 Y123.181 Z1.6
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2451.784
G1 X131.444 Y123.276 E.01663
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X128.046 Y121.66 I-2.779 J-3.338 E1.99853
G3 X130.78 Y122.66 I-.057 J4.396 E.35503
G1 X131.254 Y123.1 E.0774
G1 X130.71 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X128.051 Y122.394 I-2.309 J-2.773 E1.66197
G1 X128.17 Y122.393 E.0142
G3 X130.627 Y123.509 I-.217 J3.743 E.33037
M204 S10000
; WIPE_START
G1 F24000
G1 X130.661 Y125.509 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.117 Y126.669 Z2 F30000
G1 X122.202 Y126.81 Z2
G1 Z1.6
G1 E3 F1800
; FEATURE: Inner wall
G1 F2451.784
G1 X121.681 Y126.822 E.06235
G1 X121.642 Y126.414 E.049
G1 X122.257 Y126.309 E.07472
G3 X122.665 Y123.852 I15.4 J1.295 E.29834
G1 X122.117 Y123.553 E.07475
G1 X122.286 Y123.18 E.049
G1 X122.872 Y123.396 E.07472
G3 X124.454 Y121.472 I12.689 J8.822 E.29834
G1 X124.129 Y120.939 E.07476
G1 X124.462 Y120.701 E.049
G1 X124.861 Y121.181 E.07472
G3 X127.193 Y120.306 I6.579 J13.985 E.29834
G1 X127.178 Y119.681 E.07475
G1 X127.586 Y119.642 E.049
G1 X127.691 Y120.257 E.07472
G3 X130.148 Y120.665 I-1.295 J15.4 E.29834
G1 X130.447 Y120.117 E.07475
G1 X130.82 Y120.286 E.049
G1 X130.604 Y120.872 E.07472
G3 X132.528 Y122.454 I-8.821 J12.688 E.29834
G1 X133.061 Y122.129 E.07476
G1 X133.299 Y122.462 E.049
G1 X132.819 Y122.861 E.07472
G3 X133.694 Y125.193 I-13.985 J6.578 E.29834
G1 X134.319 Y125.178 E.07475
G1 X134.358 Y125.586 E.049
G1 X133.743 Y125.691 E.07472
G3 X133.335 Y128.148 I-15.4 J-1.295 E.29834
G1 X133.883 Y128.447 E.07476
G1 X133.714 Y128.82 E.049
G1 X133.128 Y128.604 E.07472
G3 X131.546 Y130.528 I-12.689 J-8.822 E.29834
G1 X131.871 Y131.061 E.07476
G1 X131.538 Y131.299 E.049
G1 X131.139 Y130.819 E.07472
G3 X128.807 Y131.694 I-6.579 J-13.985 E.29834
G1 X128.822 Y132.319 E.07475
G1 X128.414 Y132.358 E.049
G1 X128.309 Y131.743 E.07472
G3 X125.852 Y131.335 I1.295 J-15.4 E.29834
G1 X125.553 Y131.883 E.07475
G1 X125.18 Y131.714 E.049
G1 X125.396 Y131.128 E.07472
G3 X123.472 Y129.546 I8.821 J-12.689 E.29834
G1 X122.939 Y129.871 E.07476
G1 X122.701 Y129.538 E.049
G1 X123.181 Y129.139 E.07472
G3 X122.31 Y126.823 I13.984 J-6.578 E.29639
G1 X121.775 Y127.554 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X121.702 Y127.556 E.00872
G3 X118.984 Y127.231 I-.472 J-7.59 E.32932
G1 X118.963 Y127.071 E.01939
G3 X118.915 Y126.535 I11.794 J-1.324 E.06438
G3 X121.592 Y125.678 I3.637 J6.756 E.33819
G3 X121.832 Y124.234 I10.773 J1.047 E.17534
G1 X121.768 Y124.199 E.00872
G3 X119.576 Y122.558 I3.386 J-6.809 E.32932
G1 X119.639 Y122.409 E.01939
G3 X119.865 Y121.921 I10.878 J4.752 E.06438
G3 X122.612 Y122.517 I-.228 J7.67 E.33819
G3 X123.542 Y121.386 I8.807 J6.293 E.17534
G1 X123.504 Y121.324 E.00872
G3 X122.426 Y118.808 I6.337 J-4.204 E.32932
G1 X122.554 Y118.709 E.01939
G3 X122.995 Y118.4 I7.044 J9.552 E.06438
G3 X125.075 Y120.29 I-4.032 J6.528 E.33819
G3 X126.446 Y119.775 I4.48 J9.854 E.17534
G1 X126.444 Y119.702 E.00872
G3 X126.769 Y116.984 I7.59 J-.472 E.32932
G1 X126.929 Y116.963 E.01939
G3 X127.466 Y116.915 I1.319 J11.739 E.06451
G3 X128.322 Y119.592 I-6.793 J3.646 E.33814
G3 X129.766 Y119.832 I-1.047 J10.773 E.17534
G1 X129.801 Y119.768 E.00872
G3 X131.442 Y117.576 I6.809 J3.386 E.32932
G1 X131.591 Y117.639 E.01939
G3 X132.079 Y117.865 I-4.751 J10.878 E.06438
G3 X131.483 Y120.612 I-7.67 J-.228 E.33819
G3 X132.614 Y121.542 I-6.293 J8.806 E.17534
G1 X132.676 Y121.504 E.00872
G3 X135.192 Y120.426 I4.204 J6.337 E.32932
G1 X135.291 Y120.554 E.01939
G3 X135.6 Y120.995 I-9.552 J7.043 E.06438
G3 X133.71 Y123.075 I-6.528 J-4.032 E.33819
G3 X134.225 Y124.446 I-9.854 J4.48 E.17534
G1 X134.298 Y124.444 E.00872
G3 X137.016 Y124.769 I.472 J7.59 E.32932
G1 X137.037 Y124.929 E.01939
G3 X137.085 Y125.465 I-11.794 J1.324 E.06438
G3 X134.408 Y126.322 I-3.637 J-6.756 E.33819
G3 X134.168 Y127.766 I-10.773 J-1.047 E.17534
G1 X134.232 Y127.801 E.00872
G3 X136.424 Y129.442 I-3.386 J6.809 E.32932
G1 X136.361 Y129.591 E.01939
G3 X136.135 Y130.079 I-10.876 J-4.75 E.06438
G3 X133.388 Y129.483 I.228 J-7.67 E.33819
G3 X132.458 Y130.614 I-8.806 J-6.293 E.17534
G1 X132.496 Y130.676 E.00872
G3 X133.574 Y133.192 I-6.337 J4.204 E.32932
G1 X133.446 Y133.291 E.01939
G3 X133.005 Y133.6 I-7.044 J-9.552 E.06438
G3 X130.925 Y131.71 I4.032 J-6.528 E.33819
G3 X129.554 Y132.225 I-4.48 J-9.854 E.17534
G1 X129.556 Y132.298 E.00872
G3 X129.231 Y135.016 I-7.59 J.472 E.32932
G1 X129.071 Y135.037 E.01939
G3 X128.535 Y135.085 I-1.324 J-11.792 E.06438
G3 X127.678 Y132.408 I6.756 J-3.637 E.33819
G3 X126.234 Y132.168 I1.047 J-10.773 E.17534
G1 X126.199 Y132.232 E.00872
G3 X124.558 Y134.424 I-6.809 J-3.386 E.32932
G1 X124.409 Y134.361 E.01939
G3 X123.921 Y134.135 I4.75 J-10.876 E.06438
G3 X124.517 Y131.388 I7.67 J.228 E.33819
G3 X123.386 Y130.458 I6.293 J-8.806 E.17534
G1 X123.324 Y130.496 E.00872
G3 X120.808 Y131.574 I-4.204 J-6.337 E.32932
G1 X120.709 Y131.446 E.01939
G3 X120.4 Y131.005 I9.551 J-7.043 E.06438
G3 X122.29 Y128.925 I6.528 J4.032 E.33819
G3 X121.81 Y127.669 I9.853 J-4.48 E.16099
M204 S10000
; WIPE_START
G1 F24000
G1 X121.702 Y127.556 E-.22268
G1 X121.11 Y127.57 E-.84393
G1 X120.414 Y127.534 E-.99393
G1 X119.866 Y127.45 E-.78946
; WIPE_END
G1 E-.15 F1800
G1 X121.296 Y126.655 Z2 F30000
G1 Z1.6
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 1.04699
G1 F1872.759
G1 X120.909 Y126.692 E.06087
; LINE_WIDTH: 0.998193
G1 F1972.921
G1 X120.523 Y126.729 E.05778
; LINE_WIDTH: 0.973797
G1 F2027.126
G1 X119.311 Y126.875 E.1766
G1 X121.294 Y126.629 F30000
; LINE_WIDTH: 0.839494
G1 F2388.367
G1 X119.31 Y126.867 E.24537
G1 X119.31 Y126.861 F30000
; LINE_WIDTH: 0.666534
G1 F3000
G1 X121.293 Y126.622 E.18905
; WIPE_START
G1 F24000
G1 X119.31 Y126.861 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X120.038 Y122.413 Z2 F30000
G1 Z1.6
G1 E3 F1800
; LINE_WIDTH: 0.973793
G1 F2027.137
G1 X121.16 Y122.893 E.1766
; LINE_WIDTH: 0.998191
G1 F1972.927
G1 X121.513 Y123.054 E.05778
; LINE_WIDTH: 1.04699
G1 F1872.764
G1 X121.867 Y123.215 E.06087
M73 P63 R3
G1 X121.877 Y123.192 F30000
; LINE_WIDTH: 0.839495
G1 F2388.364
G1 X120.041 Y122.406 E.24537
G1 X120.044 Y122.4 F30000
; LINE_WIDTH: 0.666545
G1 F3000
G1 X121.881 Y123.185 E.18905
G1 X124.108 Y120.502 F30000
; LINE_WIDTH: 0.666541
G1 F3000
G1 X122.91 Y118.904 E.18905
G1 X122.904 Y118.908 F30000
; LINE_WIDTH: 0.839485
G1 F2388.395
G1 X124.102 Y120.507 E.24536
G1 X124.081 Y120.522 F30000
; LINE_WIDTH: 1.04698
G1 F1872.776
G1 X123.855 Y120.205 E.06087
; LINE_WIDTH: 0.998192
G1 F1972.924
G1 X123.63 Y119.889 E.05778
; LINE_WIDTH: 0.973798
G1 F2027.124
G1 X122.898 Y118.912 E.17661
; WIPE_START
G1 F24000
G1 X123.63 Y119.889 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X127.125 Y117.311 Z2 F30000
G1 Z1.6
G1 E3 F1800
; LINE_WIDTH: 0.973795
G1 F2027.132
G1 X127.271 Y118.523 E.1766
; LINE_WIDTH: 0.998192
G1 F1972.924
G1 X127.308 Y118.909 E.05778
; LINE_WIDTH: 1.04699
G1 F1872.763
G1 X127.345 Y119.296 E.06087
G1 X127.371 Y119.294 F30000
; LINE_WIDTH: 0.839483
G1 F2388.4
G1 X127.133 Y117.31 E.24536
G1 X127.139 Y117.31 F30000
; LINE_WIDTH: 0.666551
G1 F3000
G1 X127.378 Y119.293 E.18906
; WIPE_START
G1 F24000
G1 X127.139 Y117.31 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X131.587 Y118.038 Z2 F30000
G1 Z1.6
G1 E3 F1800
; LINE_WIDTH: 0.968543
G1 F2039.193
G1 X131.107 Y119.16 E.17556
; LINE_WIDTH: 0.998192
G1 F1972.923
G1 X131.048 Y119.289 E.02115
; LINE_WIDTH: 1.06323
G1 F1841.647
G1 X130.989 Y119.419 E.02265
G1 X130.307 Y119.608 E.11282
G1 X130.808 Y119.877 F30000
; LINE_WIDTH: 0.821189
G1 F2447.819
G1 X131.594 Y118.041 E.23941
G1 X131.6 Y118.044 F30000
; LINE_WIDTH: 0.650011
G1 F3000
G1 X130.815 Y119.881 E.18367
G1 X133.498 Y122.108 F30000
; LINE_WIDTH: 0.650024
G1 F3000
G1 X135.096 Y120.91 E.18367
G1 X135.092 Y120.904 F30000
; LINE_WIDTH: 0.82116
G1 F2447.918
G1 X133.493 Y122.102 E.23939
G1 X133.193 Y121.618 F30000
; LINE_WIDTH: 1.06323
G1 F1841.646
G1 X133.88 Y121.795 E.11291
G1 X133.995 Y121.712 E.02265
; LINE_WIDTH: 0.998189
G1 F1972.931
G1 X134.111 Y121.63 E.02114
; LINE_WIDTH: 0.968543
G1 F2039.193
G1 X135.088 Y120.898 E.17556
; WIPE_START
G1 F24000
G1 X134.111 Y121.63 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X136.689 Y125.125 Z2 F30000
G1 Z1.6
G1 E3 F1800
; LINE_WIDTH: 0.968545
G1 F2039.188
G1 X135.477 Y125.271 E.17556
; LINE_WIDTH: 0.998197
G1 F1972.914
G1 X135.336 Y125.285 E.02114
; LINE_WIDTH: 1.06325
G1 F1841.605
G1 X135.194 Y125.298 E.02265
G1 X134.686 Y124.802 E.11314
G1 X134.706 Y125.371 F30000
; LINE_WIDTH: 0.821183
G1 F2447.839
G1 X136.69 Y125.133 E.2394
G1 X136.69 Y125.139 F30000
; LINE_WIDTH: 0.650038
G1 F3000
G1 X134.707 Y125.378 E.18368
G1 X132.204 Y125.552 F30000
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.854054
G1 F2343.099
G1 X132.186 Y126.152 E.07518
; LINE_WIDTH: 0.80253
G1 F2511.55
G2 X132.168 Y127.755 I26.272 J1.102 E.18728
G1 X132.645 Y127.913 E.05868
G1 X132.879 Y126.795 E.13338
; LINE_WIDTH: 0.817448
G1 F2460.335
G1 X132.933 Y126.197 E.07159
; LINE_WIDTH: 0.865427
G1 F2308.917
G1 X132.988 Y125.599 E.07629
G1 X132.972 Y125.429 E.02171
G1 X132.643 Y124.425 E.13422
G1 X132.204 Y124.541 E.05763
G1 X132.204 Y125.432 E.11314
G1 X132.316 Y123.725 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 0.76202
G1 F2662.016
G1 X132.136 Y123.043 E.07782
; LINE_WIDTH: 0.735706
G1 F2769.805
G1 X132.076 Y122.968 E.01006
; LINE_WIDTH: 0.682943
G1 F3000
G1 X132.017 Y122.894 E.00924
G2 X130.759 Y121.817 I-7.289 J7.239 E.16133
; LINE_WIDTH: 0.695255
G1 F2953.655
G1 X130.547 Y121.676 E.02527
; LINE_WIDTH: 0.724855
G1 F2816.839
G2 X130.305 Y121.517 I-3.073 J4.394 E.03018
; LINE_WIDTH: 0.755615
G1 F2687.471
G1 X130.199 Y121.454 E.01342
; LINE_WIDTH: 0.772024
G1 F2623.207
G2 X129.842 Y121.309 I-.513 J.749 E.04351
; LINE_WIDTH: 0.736423
G1 F2766.753
G1 X129.808 Y121.299 E.00373
; LINE_WIDTH: 0.720331
G1 F2836.925
G1 X129.562 Y121.232 E.02631
; LINE_WIDTH: 0.681885
G1 F3000
G2 X128.219 Y120.991 I-1.755 J5.92 E.1328
; LINE_WIDTH: 0.70241
G1 F2919.381
G1 X127.965 Y120.977 E.02558
; LINE_WIDTH: 0.736334
G1 F2767.131
G2 X127.675 Y120.962 I-.424 J5.365 E.03082
; LINE_WIDTH: 0.765573
G1 F2648.101
G1 X127.509 Y120.962 E.01843
G1 X127.172 Y121.035 E.03817
; LINE_WIDTH: 0.724496
G1 F2818.423
G1 X127.138 Y121.043 E.00359
; LINE_WIDTH: 0.686073
G1 F2998.841
G2 X125.615 Y121.587 I1.53 J6.698 E.15863
; LINE_WIDTH: 0.710819
G1 F2880.098
G1 X125.388 Y121.704 E.02594
; LINE_WIDTH: 0.749087
G1 F2713.923
G2 X125.13 Y121.838 I2.357 J4.847 E.03152
; LINE_WIDTH: 0.781995
G1 F2585.634
G1 X125.055 Y121.882 E.00982
; LINE_WIDTH: 0.773503
G1 F2617.563
G1 X124.899 Y122.026 E.02376
; LINE_WIDTH: 0.732212
G1 F2784.779
G2 X124.719 Y122.193 I3.018 J3.431 E.02591
; LINE_WIDTH: 0.685103
G1 F3000
G2 X123.684 Y123.436 I4.839 J5.082 E.15837
; LINE_WIDTH: 0.720474
G1 F2836.283
G1 X123.548 Y123.652 E.02636
; LINE_WIDTH: 0.763667
G1 F2655.55
G2 X123.389 Y123.905 I3.874 J2.597 E.03306
; LINE_WIDTH: 0.768655
G1 F2636.148
G1 X123.316 Y124.146 E.02801
; LINE_WIDTH: 0.724405
G1 F2818.823
G2 X123.234 Y124.419 I5.027 J1.658 E.02967
; LINE_WIDTH: 0.685014
G1 F3000
G2 X122.975 Y126.017 I6.891 J1.936 E.15837
; LINE_WIDTH: 0.729887
G1 F2794.831
G1 X122.968 Y126.254 E.02492
; LINE_WIDTH: 0.773149
G1 F2618.912
G2 X122.974 Y126.563 I.7 J.139 E.03486
; LINE_WIDTH: 0.754991
G1 F2689.977
G1 X123.034 Y126.81 E.02778
; LINE_WIDTH: 0.714501
G1 F2863.234
G2 X123.102 Y127.09 I5.219 J-1.128 E.02948
; LINE_WIDTH: 0.685802
G1 F3000
G2 X123.693 Y128.598 I6.977 J-1.862 E.15864
; LINE_WIDTH: 0.738211
G1 F2759.17
G1 X123.787 Y128.771 E.02103
; LINE_WIDTH: 0.775248
G1 F2610.938
G2 X123.982 Y129.059 I.903 J-.402 E.03924
; LINE_WIDTH: 0.741789
G1 F2744.12
G1 X124.159 Y129.242 E.02722
; LINE_WIDTH: 0.691082
G1 F2974.023
G2 X124.695 Y129.759 I5.297 J-4.945 E.07346
; LINE_WIDTH: 0.677354
G1 F3000
G1 X124.756 Y129.814 E.00794
G2 X125.184 Y130.143 I14.475 J-18.384 E.05206
; LINE_WIDTH: 0.701992
G1 F2921.359
G1 X125.606 Y130.427 E.05108
; LINE_WIDTH: 0.72862
G1 F2800.339
G1 X125.635 Y130.446 E.00364
; LINE_WIDTH: 0.747168
G1 F2721.799
G1 X125.771 Y130.527 E.01703
; LINE_WIDTH: 0.775774
G1 F2608.949
G2 X126.091 Y130.671 I.49 J-.664 E.03976
; LINE_WIDTH: 0.747979
G1 F2718.467
G1 X126.126 Y130.681 E.00387
; LINE_WIDTH: 0.729829
G1 F2795.083
G1 X126.371 Y130.749 E.02671
; LINE_WIDTH: 0.682908
G1 F3000
G2 X127.711 Y131.003 I1.807 J-5.884 E.13304
; LINE_WIDTH: 0.696038
G1 F2949.867
G1 X127.965 Y131.019 E.0253
; LINE_WIDTH: 0.726149
G1 F2811.147
G2 X128.255 Y131.036 I.459 J-5.341 E.03025
; LINE_WIDTH: 0.756788
G1 F2682.776
G1 X128.373 Y131.037 E.01293
; LINE_WIDTH: 0.771359
G1 F2625.75
G2 X128.76 Y130.981 I.067 J-.916 E.04401
; LINE_WIDTH: 0.734941
G1 F2773.069
G1 X128.794 Y130.973 E.00371
; LINE_WIDTH: 0.719124
G1 F2842.328
G1 X129.04 Y130.908 E.02626
; LINE_WIDTH: 0.681795
G1 F3000
G2 X130.323 Y130.443 I-1.455 J-6.022 E.13277
; LINE_WIDTH: 0.703347
G1 F2914.949
G1 X130.55 Y130.328 E.02562
; LINE_WIDTH: 0.737785
G1 F2760.974
G2 X130.809 Y130.196 I-2.32 J-4.855 E.0309
; LINE_WIDTH: 0.765002
G1 F2650.328
G1 X130.944 Y130.117 E.01736
G1 X131.206 Y129.879 E.03919
; LINE_WIDTH: 0.723158
G1 F2824.341
G1 X131.231 Y129.855 E.00358
; LINE_WIDTH: 0.704122
G1 F2911.295
G1 X131.499 Y129.584 E.03844
; LINE_WIDTH: 0.670906
G1 F3000
G1 X131.767 Y129.313 E.03637
; LINE_WIDTH: 0.633295
G2 X131.995 Y129.07 I-10.133 J-9.769 E.02969
; LINE_WIDTH: 0.623312
G1 X132.048 Y128.977 E.00936
; LINE_WIDTH: 0.650519
G1 X132.1 Y128.884 E.00983
; LINE_WIDTH: 0.664123
G1 X132.217 Y128.534 E.03481
G1 X134.119 Y128.815 F30000
; LINE_WIDTH: 0.650026
G1 F3000
G1 X135.956 Y129.6 E.18368
G1 X135.959 Y129.594 F30000
; LINE_WIDTH: 0.821176
G1 F2447.864
G1 X134.123 Y128.808 E.2394
G1 X134.391 Y128.306 F30000
; LINE_WIDTH: 1.06323
G1 F1841.636
G1 X134.581 Y128.989 E.11296
G1 X134.711 Y129.048 E.02265
; LINE_WIDTH: 0.99819
G1 F1972.929
G1 X134.84 Y129.107 E.02114
; LINE_WIDTH: 0.968544
G1 F2039.19
G1 X135.962 Y129.587 E.17556
; WIPE_START
G1 F24000
G1 X134.84 Y129.107 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X133.102 Y133.088 Z2 F30000
G1 Z1.6
G1 E3 F1800
; LINE_WIDTH: 0.968545
G1 F2039.187
G1 X132.37 Y132.111 E.17556
; LINE_WIDTH: 0.998194
G1 F1972.921
G1 X132.288 Y131.995 E.02114
; LINE_WIDTH: 1.06323
G1 F1841.634
G1 X132.205 Y131.88 E.02265
G1 X132.382 Y131.193 E.11295
G1 X131.898 Y131.493 F30000
; LINE_WIDTH: 0.821168
G1 F2447.889
G1 X133.096 Y133.092 E.2394
G1 X133.09 Y133.096 F30000
; LINE_WIDTH: 0.650019
G1 F3000
G1 X131.892 Y131.498 E.18367
G1 X128.622 Y132.707 F30000
; LINE_WIDTH: 0.666553
G1 F3000
G1 X128.861 Y134.69 E.18906
G1 X128.867 Y134.69 F30000
; LINE_WIDTH: 0.839475
G1 F2388.427
G1 X128.629 Y132.706 E.24536
G1 X129.198 Y132.687 F30000
; LINE_WIDTH: 1.07104
G1 F1827.033
G1 X128.702 Y133.194 E.1139
; LINE_WIDTH: 1.04699
G1 F1872.758
G1 X128.715 Y133.336 E.02227
; LINE_WIDTH: 0.998197
G1 F1972.914
G1 X128.729 Y133.477 E.02114
; LINE_WIDTH: 0.973799
G1 F2027.121
G1 X128.875 Y134.689 E.17661
; WIPE_START
G1 F24000
G1 X128.729 Y133.477 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X124.413 Y133.962 Z2 F30000
G1 Z1.6
G1 E3 F1800
; LINE_WIDTH: 0.973792
G1 F2027.138
G1 X124.893 Y132.84 E.1766
; LINE_WIDTH: 0.998192
G1 F1972.925
G1 X125.054 Y132.487 E.05778
; LINE_WIDTH: 1.04699
G1 F1872.757
G1 X125.215 Y132.133 E.06087
G1 X125.192 Y132.123 F30000
; LINE_WIDTH: 0.839493
G1 F2388.368
G1 X124.406 Y133.959 E.24537
G1 X124.4 Y133.956 F30000
; LINE_WIDTH: 0.666545
G1 F3000
G1 X125.185 Y132.119 E.18906
G1 X122.502 Y129.892 F30000
; LINE_WIDTH: 0.666552
G1 F3000
G1 X120.904 Y131.09 E.18905
G1 X120.908 Y131.096 F30000
; LINE_WIDTH: 0.839484
G1 F2388.398
G1 X122.507 Y129.898 E.24536
G1 X122.522 Y129.919 F30000
; LINE_WIDTH: 1.04698
G1 F1872.774
G1 X122.205 Y130.145 E.06087
; LINE_WIDTH: 0.998192
G1 F1972.924
G1 X121.889 Y130.37 E.05778
; LINE_WIDTH: 0.973798
G1 F2027.124
G1 X120.912 Y131.102 E.17661
; CHANGE_LAYER
; Z_HEIGHT: 2
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X121.889 Y130.37 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 5/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L5
M991 S0 P4 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z2 I.737 J.969 P1  F30000
G1 X131.342 Y123.182 Z2
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2451.784
G1 X131.444 Y123.276 E.0166
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X123.725 Y125.253 I-2.778 J-3.337 E1.26691
G1 X123.725 Y125.253 E0
G3 X128.018 Y121.66 I4.258 J.727 E.72873
G3 X130.78 Y122.66 I-.028 J4.392 E.35833
G1 X131.255 Y123.1 E.07743
G1 X130.71 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X128.023 Y122.394 I-2.309 J-2.773 E1.65865
G1 X128.17 Y122.393 E.01751
G3 X130.627 Y123.509 I-.217 J3.743 E.33037
M204 S10000
; WIPE_START
G1 F24000
G1 X130.661 Y125.509 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.141 Y126.812 Z2.4 F30000
G1 X122.224 Y126.971 Z2.4
G1 Z2
G1 E3 F1800
; FEATURE: Inner wall
G1 F2451.784
G1 X121.702 Y126.998 E.06261
G1 X121.651 Y126.592 E.04897
G1 X122.265 Y126.468 E.07493
G3 X122.605 Y124 I16.531 J1.018 E.29841
G1 X122.047 Y123.715 E.07497
G1 X122.206 Y123.338 E.04897
G1 X122.799 Y123.538 E.07493
G3 X124.327 Y121.57 I13.809 J9.148 E.29841
G1 X123.987 Y121.044 E.07497
G1 X124.313 Y120.797 E.04897
G1 X124.727 Y121.267 E.07493
G3 X127.034 Y120.327 I7.385 J14.828 E.29841
G1 X127.002 Y119.702 E.07497
G1 X127.408 Y119.651 E.04897
G1 X127.532 Y120.265 E.07493
G3 X130 Y120.605 I-1.018 J16.531 E.29841
G1 X130.285 Y120.047 E.07497
G1 X130.662 Y120.206 E.04897
G1 X130.462 Y120.799 E.07493
G3 X132.43 Y122.327 I-9.148 J13.808 E.29841
G1 X132.956 Y121.987 E.07497
G1 X133.203 Y122.313 E.04897
G1 X132.733 Y122.727 E.07493
G3 X133.673 Y125.034 I-14.829 J7.385 E.29841
G1 X134.298 Y125.002 E.07496
G1 X134.349 Y125.408 E.04897
G1 X133.735 Y125.532 E.07492
G3 X133.395 Y128 I-16.531 J-1.018 E.29841
G1 X133.953 Y128.285 E.07496
G1 X133.794 Y128.662 E.04897
G1 X133.201 Y128.462 E.07492
G3 X131.673 Y130.43 I-13.809 J-9.148 E.29841
G1 X132.013 Y130.956 E.07497
G1 X131.687 Y131.203 E.04897
G1 X131.273 Y130.733 E.07493
M73 P64 R3
G3 X128.966 Y131.673 I-7.385 J-14.828 E.29841
G1 X128.998 Y132.298 E.07497
G1 X128.592 Y132.349 E.04897
G1 X128.468 Y131.735 E.07493
G3 X126 Y131.395 I1.018 J-16.531 E.29841
G1 X125.715 Y131.953 E.07496
G1 X125.338 Y131.794 E.04897
G1 X125.538 Y131.201 E.07492
G3 X123.57 Y129.673 I9.148 J-13.808 E.29841
G1 X123.044 Y130.013 E.07497
G1 X122.797 Y129.687 E.04897
G1 X123.267 Y129.273 E.07493
G3 X122.333 Y126.982 I14.828 J-7.385 E.29642
G1 X121.819 Y127.727 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X121.747 Y127.731 E.00868
G3 X119.022 Y127.481 I-.68 J-7.586 E.32923
G3 X118.996 Y127.321 I1.826 J-.374 E.01945
G3 X118.935 Y126.786 I6.091 J-.969 E.06439
G3 X121.584 Y125.856 I3.704 J6.312 E.33807
G3 X121.784 Y124.405 I11.563 J.852 E.17537
G1 X121.719 Y124.372 E.00868
G3 X119.484 Y122.793 I3.204 J-6.909 E.32923
G3 X119.542 Y122.642 I1.768 J.59 E.01945
G3 X119.757 Y122.148 I5.213 J1.981 E.06445
G3 X122.516 Y122.668 I-.019 J7.687 E.33774
G3 X123.414 Y121.511 I9.588 J6.52 E.17537
G1 X123.375 Y121.45 E.00868
G3 X122.228 Y118.965 I6.229 J-4.382 E.32923
G3 X122.354 Y118.863 I1.237 J1.395 E.01945
G3 X122.787 Y118.543 I3.525 J4.323 E.06445
G3 X124.917 Y120.372 I-3.86 J6.647 E.33774
G3 X126.273 Y119.819 I5.044 J10.441 E.17537
G1 X126.269 Y119.747 E.00868
G3 X126.519 Y117.022 I7.586 J-.68 E.32923
G3 X126.679 Y116.996 I.374 J1.826 E.01945
G3 X127.214 Y116.936 I.891 J5.506 E.06446
G3 X128.144 Y119.584 I-6.669 J3.827 E.33773
G3 X129.595 Y119.784 I-.852 J11.563 E.17537
G1 X129.628 Y119.719 E.00868
G3 X131.207 Y117.484 I6.909 J3.204 E.32923
G3 X131.358 Y117.542 I-.59 J1.769 E.01945
G3 X131.852 Y117.757 I-1.981 J5.213 E.06445
G3 X131.332 Y120.516 I-7.687 J-.019 E.33774
G3 X132.489 Y121.414 I-6.52 J9.588 E.17537
G1 X132.55 Y121.375 E.00868
G3 X135.035 Y120.228 I4.382 J6.229 E.32923
G3 X135.137 Y120.354 I-1.395 J1.236 E.01945
G3 X135.457 Y120.787 I-4.324 J3.526 E.06445
G3 X133.628 Y122.917 I-6.647 J-3.86 E.33774
G3 X134.181 Y124.273 I-10.442 J5.044 E.17537
G1 X134.253 Y124.269 E.00868
G3 X136.978 Y124.519 I.68 J7.586 E.32923
G3 X137.004 Y124.679 I-1.826 J.374 E.01945
G3 X137.065 Y125.214 I-6.092 J.969 E.06439
G3 X134.416 Y126.144 I-3.704 J-6.312 E.33807
G3 X134.216 Y127.595 I-11.562 J-.852 E.17537
G1 X134.281 Y127.628 E.00868
G3 X136.516 Y129.207 I-3.204 J6.909 E.32923
G3 X136.458 Y129.358 I-1.768 J-.59 E.01945
G3 X136.243 Y129.852 I-5.213 J-1.981 E.06445
G3 X133.484 Y129.332 I.019 J-7.687 E.33774
G3 X132.586 Y130.489 I-9.588 J-6.52 E.17537
G1 X132.625 Y130.55 E.00868
G3 X133.772 Y133.035 I-6.229 J4.381 E.32923
G3 X133.646 Y133.137 I-1.236 J-1.394 E.01945
G3 X133.213 Y133.457 I-3.526 J-4.323 E.06445
G3 X131.083 Y131.628 I3.86 J-6.647 E.33774
G3 X129.727 Y132.181 I-5.044 J-10.441 E.17537
G1 X129.731 Y132.253 E.00868
G3 X129.481 Y134.978 I-7.586 J.68 E.32923
G3 X129.321 Y135.004 I-.374 J-1.826 E.01945
G3 X128.786 Y135.065 I-.968 J-6.09 E.06439
G3 X127.856 Y132.416 I6.313 J-3.704 E.33807
G3 X126.405 Y132.216 I.852 J-11.562 E.17537
G1 X126.372 Y132.281 E.00868
G3 X124.793 Y134.516 I-6.909 J-3.204 E.32923
G3 X124.642 Y134.458 I.59 J-1.769 E.01945
G3 X124.148 Y134.243 I1.981 J-5.214 E.06445
G3 X124.668 Y131.484 I7.687 J.019 E.33774
G3 X123.511 Y130.586 I6.52 J-9.588 E.17537
G1 X123.45 Y130.625 E.00868
G3 X120.965 Y131.772 I-4.382 J-6.229 E.32923
G3 X120.863 Y131.646 I1.395 J-1.237 E.01945
G3 X120.543 Y131.213 I4.323 J-3.525 E.06445
G3 X122.372 Y129.083 I6.647 J3.86 E.33774
G3 X121.858 Y127.84 I10.442 J-5.044 E.16101
M204 S10000
G1 X121.343 Y127.384 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 1.06264
G1 F1842.745
G1 X120.824 Y126.903 E.11266
G1 X120.696 Y126.917 E.02052
; LINE_WIDTH: 1.01121
G1 F1945.164
G1 X120.017 Y127.009 E.10341
; LINE_WIDTH: 0.994808
G1 F1980.27
G1 X119.338 Y127.102 E.10158
; WIPE_START
G1 F24000
G1 X120.017 Y127.009 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X119.942 Y122.636 Z2.4 F30000
G1 Z2
G1 E3 F1800
; LINE_WIDTH: 0.973725
G1 F2027.29
G1 X121.076 Y123.084 E.17651
; LINE_WIDTH: 0.997752
G1 F1973.875
G1 X121.432 Y123.234 E.05737
; LINE_WIDTH: 1.0458
G1 F1875.071
G1 X121.787 Y123.385 E.0604
G1 X121.797 Y123.361 F30000
; LINE_WIDTH: 0.83942
G1 F2388.6
G1 X119.945 Y122.629 E.24466
G1 X119.947 Y122.623 F30000
; LINE_WIDTH: 0.666468
G1 F3000
G1 X121.8 Y123.354 E.18852
G1 X123.954 Y120.609 F30000
; LINE_WIDTH: 0.666488
G1 F3000
G1 X122.715 Y119.049 E.18852
G1 X122.709 Y119.053 F30000
; LINE_WIDTH: 0.839417
G1 F2388.61
G1 X123.948 Y120.613 E.24466
G1 X123.927 Y120.629 F30000
; LINE_WIDTH: 1.0458
G1 F1875.08
G1 X123.695 Y120.321 E.0604
; LINE_WIDTH: 0.997739
G1 F1973.905
G1 X123.462 Y120.013 E.05737
; LINE_WIDTH: 0.97371
G1 F2027.326
G1 X122.703 Y119.058 E.1765
; WIPE_START
G1 F24000
G1 X123.462 Y120.013 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X126.884 Y117.339 Z2.4 F30000
G1 Z2
G1 E3 F1800
; LINE_WIDTH: 0.973728
G1 F2027.284
G1 X127.064 Y118.546 E.17651
; LINE_WIDTH: 0.997753
G1 F1973.873
G1 X127.111 Y118.929 E.05737
; LINE_WIDTH: 1.0458
G1 F1875.073
G1 X127.159 Y119.312 E.06039
G1 X127.184 Y119.309 F30000
; LINE_WIDTH: 0.839405
G1 F2388.648
G1 X126.892 Y117.338 E.24466
G1 X126.898 Y117.337 F30000
; LINE_WIDTH: 0.666481
G1 F3000
G1 X127.191 Y119.308 E.18852
G1 X130.639 Y119.797 F30000
; LINE_WIDTH: 0.821116
G1 F2448.063
G1 X131.371 Y117.945 E.23872
G1 X131.377 Y117.947 F30000
; LINE_WIDTH: 0.649961
G1 F3000
G1 X130.646 Y119.8 E.18316
G1 X131.13 Y119.967 F30000
; LINE_WIDTH: 1.06192
G1 F1844.114
G1 X130.807 Y119.334 E.11305
G1 X130.862 Y119.205 E.02228
; LINE_WIDTH: 0.997752
G1 F1973.875
G1 X130.916 Y119.076 E.02081
; LINE_WIDTH: 0.968468
G1 F2039.366
G1 X131.364 Y117.942 E.17547
; WIPE_START
G1 F24000
G1 X130.916 Y119.076 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X136.278 Y124.508 Z2.4 F30000
G1 X136.662 Y124.898 Z2.4
G1 Z2
G1 E3 F1800
; LINE_WIDTH: 0.978401
G1 F2016.67
G1 X135.983 Y124.991 E.09974
; LINE_WIDTH: 1.01121
G1 F1945.177
G1 X135.304 Y125.083 E.10341
; LINE_WIDTH: 1.0624
G1 F1843.208
G1 X135.176 Y125.097 E.02052
G1 X134.657 Y124.616 E.11263
; WIPE_START
G1 F24000
G1 X135.176 Y125.097 E-2.41076
G1 X135.304 Y125.083 E-.43924
; WIPE_END
G1 E-.15 F1800
G1 X134.942 Y120.703 Z2.4 F30000
G1 Z2
G1 E3 F1800
; LINE_WIDTH: 0.968465
G1 F2039.373
G1 X133.987 Y121.462 E.17546
; LINE_WIDTH: 0.997745
G1 F1973.891
G1 X133.876 Y121.546 E.02081
; LINE_WIDTH: 1.0619
G1 F1844.156
G1 X133.764 Y121.631 E.02228
G1 X133.073 Y121.473 E.1127
G1 X133.387 Y121.948 F30000
; LINE_WIDTH: 0.821101
G1 F2448.113
G1 X134.947 Y120.709 E.23871
G1 X134.951 Y120.715 F30000
; LINE_WIDTH: 0.649976
G1 F3000
G1 X133.391 Y121.954 E.18316
G1 X132.381 Y123.714 F30000
; LINE_WIDTH: 0.737043
G1 F2764.117
G1 X132.064 Y122.919 E.0908
G1 X132.027 Y122.883 E.00551
; LINE_WIDTH: 0.69176
G1 F2970.695
G2 X131.191 Y122.142 I-9.576 J9.957 E.1104
G2 X130.331 Y121.543 I-5.291 J6.687 E.10354
; LINE_WIDTH: 0.72086
G1 F2834.561
G1 X130.301 Y121.525 E.00355
; LINE_WIDTH: 0.741725
G1 F2744.386
G1 X130.133 Y121.429 E.02068
; LINE_WIDTH: 0.778387
G1 F2599.104
G2 X129.812 Y121.286 I-.566 J.838 E.03991
; LINE_WIDTH: 0.742981
G1 F2739.142
G1 X129.565 Y121.223 E.02727
; LINE_WIDTH: 0.691821
G1 F2970.392
G2 X128.849 Y121.067 I-1.879 J6.889 E.07243
; LINE_WIDTH: 0.677454
G1 F3000
G1 X128.757 Y121.051 E.00904
G2 X128.22 Y120.995 I-2.927 J25.527 E.05207
; LINE_WIDTH: 0.691778
G1 F2970.606
G1 X127.965 Y120.984 E.02512
; LINE_WIDTH: 0.718901
G1 F2843.332
G2 X127.676 Y120.973 I-.356 J5.343 E.02985
; LINE_WIDTH: 0.750946
M73 P65 R3
G1 F2706.339
G1 X127.523 Y120.975 E.01667
; LINE_WIDTH: 0.778637
G1 F2598.167
G2 X127.171 Y121.022 I-.068 J.82 E.04043
; LINE_WIDTH: 0.749284
G1 F2713.117
G1 X127.136 Y121.031 E.00388
; LINE_WIDTH: 0.730925
G1 F2790.333
G1 X126.891 Y121.102 E.02676
; LINE_WIDTH: 0.683263
G1 F3000
G2 X125.617 Y121.591 I1.593 J6.063 E.13313
; LINE_WIDTH: 0.698227
G1 F2939.322
G1 X125.392 Y121.71 E.0254
; LINE_WIDTH: 0.729663
G1 F2795.804
G2 X125.137 Y121.847 I2.408 J4.8 E.03045
; LINE_WIDTH: 0.760824
G1 F2666.732
G1 X125.039 Y121.906 E.01253
; LINE_WIDTH: 0.773834
G1 F2616.306
G2 X124.736 Y122.16 I.423 J.812 E.04467
; LINE_WIDTH: 0.736123
G1 F2768.03
G1 X124.711 Y122.185 E.00373
; LINE_WIDTH: 0.720102
G1 F2837.949
G1 X124.537 Y122.37 E.0263
; LINE_WIDTH: 0.682202
G1 F3000
G2 X123.689 Y123.439 I4.526 J4.462 E.13287
; LINE_WIDTH: 0.705914
G1 F2902.883
G1 X123.555 Y123.656 E.02573
; LINE_WIDTH: 0.74168
G1 F2744.575
G2 X123.404 Y123.904 I4.523 J2.927 E.03111
; LINE_WIDTH: 0.767437
G1 F2640.861
G1 X123.333 Y124.035 E.01646
G1 X123.233 Y124.383 E.0403
; LINE_WIDTH: 0.700861
G1 F2926.734
G2 X123.111 Y124.912 I9.725 J2.526 E.05444
; LINE_WIDTH: 0.680595
G1 F3000
G2 X122.982 Y126.016 I7.201 J1.402 E.10785
; LINE_WIDTH: 0.714848
G1 F2861.654
G1 X122.977 Y126.271 E.02611
; LINE_WIDTH: 0.754967
G1 F2690.075
G2 X122.972 Y126.563 I5.399 J.231 E.03185
; LINE_WIDTH: 0.786869
G1 F2567.658
G1 X122.975 Y126.631 E.0078
; LINE_WIDTH: 0.775584
G1 F2609.668
G1 X123.03 Y126.845 E.02485
; LINE_WIDTH: 0.732757
G1 F2782.432
G2 X123.094 Y127.092 I4.611 J-1.074 E.02689
; LINE_WIDTH: 0.68567
G1 F3000
G2 X123.699 Y128.593 I6.955 J-1.93 E.15854
; LINE_WIDTH: 0.725043
G1 F2816.008
G1 X123.824 Y128.815 E.02655
; LINE_WIDTH: 0.769407
G1 F2633.248
G2 X123.97 Y129.069 I1.023 J-.423 E.0327
; LINE_WIDTH: 0.769086
G1 F2634.486
G1 X124.15 Y129.249 E.02839
; LINE_WIDTH: 0.724425
G1 F2818.734
G2 X124.354 Y129.453 I3.884 J-3.69 E.03001
; LINE_WIDTH: 0.685781
G1 F3000
G2 X125.639 Y130.438 I5.086 J-5.302 E.1586
; LINE_WIDTH: 0.734128
G1 F2776.549
G1 X125.837 Y130.553 E.02414
; LINE_WIDTH: 0.777259
G1 F2603.345
G2 X126.121 Y130.695 I.474 J-.594 E.03606
; LINE_WIDTH: 0.754652
G1 F2691.341
G1 X126.367 Y130.759 E.02777
; LINE_WIDTH: 0.714291
G1 F2864.187
G2 X126.646 Y130.831 I1.474 J-5.133 E.02947
; LINE_WIDTH: 0.686034
G1 F2999.033
G1 X127.175 Y130.938 E.05281
G2 X128.219 Y131.025 I1.238 J-8.554 E.10257
; LINE_WIDTH: 0.722156
G1 F2828.787
G1 X128.254 Y131.026 E.00357
; LINE_WIDTH: 0.742783
G1 F2739.966
G1 X128.443 Y131.025 E.02021
; LINE_WIDTH: 0.77828
G1 F2599.506
G2 X128.797 Y130.986 I.063 J-1.049 E.04042
; LINE_WIDTH: 0.74149
G1 F2745.371
G1 X129.042 Y130.917 E.02721
; LINE_WIDTH: 0.691439
G1 F2972.268
G2 X129.731 Y130.696 I-1.799 J-6.817 E.07146
; LINE_WIDTH: 0.677526
G1 F3000
G1 X129.828 Y130.661 E.00994
G2 X130.321 Y130.44 I-11.103 J-25.43 E.05208
; LINE_WIDTH: 0.692484
G1 F2967.148
G1 X130.546 Y130.322 E.02515
; LINE_WIDTH: 0.720119
G1 F2837.872
G2 X130.802 Y130.187 I-2.37 J-4.807 E.02992
; LINE_WIDTH: 0.752092
G1 F2701.685
G1 X130.93 Y130.111 E.01618
; LINE_WIDTH: 0.778215
G1 F2599.749
G2 X131.214 Y129.889 I-.36 J-.753 E.04095
; LINE_WIDTH: 0.747649
G1 F2719.823
G1 X131.239 Y129.864 E.00386
; LINE_WIDTH: 0.726878
G1 F2807.948
G1 X131.447 Y129.647 E.03136
; LINE_WIDTH: 0.691488
G1 F2972.029
G1 X131.655 Y129.431 E.02963
; LINE_WIDTH: 0.656097
G1 F3000
G1 X131.862 Y129.214 E.0279
; LINE_WIDTH: 0.62209
G1 X131.977 Y129.09 E.01478
G2 X132.074 Y128.951 I-.43 J-.4 E.01485
; LINE_WIDTH: 0.644656
G1 X132.099 Y128.884 E.0065
; LINE_WIDTH: 0.675058
G1 X132.16 Y128.694 E.01918
; LINE_WIDTH: 0.688009
G1 F2989.196
G1 X132.22 Y128.503 E.0196
G1 X132.173 Y126.625 F30000
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.808718
G1 F2490.05
G1 X132.173 Y127.724 E.12948
G1 X132.676 Y127.884 E.06224
G1 X132.894 Y126.66 E.1465
; LINE_WIDTH: 0.823258
G1 F2440.953
G1 X132.937 Y126.06 E.07223
; LINE_WIDTH: 0.86396
G1 F2313.271
G1 X132.981 Y125.461 E.07622
G1 X132.96 Y125.29 E.02178
G1 X132.647 Y124.424 E.11683
G1 X132.202 Y124.601 E.06072
G1 X132.202 Y125.423 E.10423
; LINE_WIDTH: 0.852338
G1 F2348.346
G1 X132.189 Y125.964 E.06759
; LINE_WIDTH: 0.837798
G1 F2393.754
G1 X132.176 Y126.505 E.06631
G1 X134.2 Y128.646 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 0.649987
G1 F3000
G1 X136.053 Y129.377 E.18317
G1 X136.055 Y129.371 F30000
; LINE_WIDTH: 0.82111
G1 F2448.083
G1 X134.203 Y128.639 E.23872
G1 X134.457 Y128.13 F30000
; LINE_WIDTH: 1.06191
G1 F1844.135
G1 X134.666 Y128.807 E.11272
G1 X134.795 Y128.862 E.02228
; LINE_WIDTH: 0.997757
G1 F1973.865
G1 X134.924 Y128.916 E.02081
; LINE_WIDTH: 0.968466
G1 F2039.37
G1 X136.058 Y129.364 E.17547
; WIPE_START
G1 F24000
G1 X134.924 Y128.916 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X133.297 Y132.942 Z2.4 F30000
G1 Z2
G1 E3 F1800
; LINE_WIDTH: 0.968466
G1 F2039.37
G1 X132.538 Y131.987 E.17547
; LINE_WIDTH: 0.997753
G1 F1973.874
G1 X132.454 Y131.876 E.02081
; LINE_WIDTH: 1.0619
G1 F1844.152
G1 X132.369 Y131.764 E.02228
G1 X132.527 Y131.073 E.1127
G1 X132.052 Y131.387 F30000
; LINE_WIDTH: 0.821109
G1 F2448.086
G1 X133.291 Y132.947 E.23872
G1 X133.285 Y132.951 F30000
; LINE_WIDTH: 0.64997
G1 F3000
G1 X132.046 Y131.391 E.18316
G1 X129.384 Y132.657 F30000
; LINE_WIDTH: 1.06261
G1 F1842.803
G1 X128.903 Y133.176 E.11267
G1 X128.917 Y133.304 E.02052
; LINE_WIDTH: 1.01121
G1 F1945.178
G1 X129.009 Y133.983 E.10341
; LINE_WIDTH: 0.994803
G1 F1980.28
G1 X129.102 Y134.662 E.10158
; WIPE_START
G1 F24000
G1 X129.009 Y133.983 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X124.636 Y134.058 Z2.4 F30000
G1 Z2
G1 E3 F1800
; LINE_WIDTH: 0.973732
G1 F2027.274
G1 X125.084 Y132.924 E.17652
; LINE_WIDTH: 0.997757
G1 F1973.865
G1 X125.234 Y132.568 E.05737
; LINE_WIDTH: 1.04581
G1 F1875.059
G1 X125.385 Y132.213 E.0604
G1 X125.361 Y132.203 F30000
; LINE_WIDTH: 0.839419
G1 F2388.603
G1 X124.629 Y134.055 E.24467
G1 X124.623 Y134.053 F30000
; LINE_WIDTH: 0.666469
G1 F3000
G1 X125.354 Y132.2 E.18852
G1 X122.609 Y130.046 F30000
; LINE_WIDTH: 0.666465
G1 F3000
G1 X121.049 Y131.285 E.18851
G1 X121.053 Y131.291 F30000
; LINE_WIDTH: 0.839411
G1 F2388.629
G1 X122.613 Y130.052 E.24466
G1 X122.629 Y130.073 F30000
; LINE_WIDTH: 1.04581
G1 F1875.07
G1 X122.321 Y130.305 E.06039
; LINE_WIDTH: 0.997756
G1 F1973.867
G1 X122.013 Y130.538 E.05737
; LINE_WIDTH: 0.973734
G1 F2027.271
G1 X121.058 Y131.297 E.17652
; CHANGE_LAYER
; Z_HEIGHT: 2.4
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X122.013 Y130.538 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 6/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L6
M991 S0 P5 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z2.4 I.753 J.956 P1  F30000
G1 X131.343 Y123.182 Z2.4
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2409
G1 X131.444 Y123.276 E.01656
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X127.991 Y121.66 I-2.777 J-3.338 E1.99101
G3 X130.78 Y122.66 I.001 J4.389 E.36163
G1 X131.255 Y123.1 E.07747
G1 X130.71 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2409
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X127.996 Y122.395 I-2.307 J-2.773 E1.65459
G1 X128.17 Y122.393 E.02081
G3 X130.627 Y123.509 I-.217 J3.743 E.33037
M204 S10000
; WIPE_START
G1 F24000
G1 X130.661 Y125.509 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.167 Y126.955 Z2.8 F30000
G1 X122.263 Y127.129 Z2.8
G1 Z2.4
G1 E3 F1800
; FEATURE: Inner wall
G1 F2409
G1 X121.804 Y127.166 E.05505
G1 X121.745 Y126.757 E.04947
G1 X122.285 Y126.644 E.06595
G3 X122.563 Y124.155 I13.96 J.3 E.30004
G1 X122.051 Y123.912 E.06776
G1 X122.205 Y123.528 E.04947
G1 X122.728 Y123.7 E.06595
G3 X124.214 Y121.684 I11.94 J7.24 E.30004
G1 X123.892 Y121.217 E.06776
G1 X124.217 Y120.962 E.04947
G1 X124.585 Y121.372 E.06595
G3 X126.879 Y120.369 I6.72 J12.239 E.30004
G1 X126.834 Y119.804 E.06776
G1 X127.243 Y119.745 E.04947
G1 X127.356 Y120.285 E.06595
G3 X129.845 Y120.563 I-.3 J13.96 E.30004
G1 X130.088 Y120.051 E.06776
G1 X130.472 Y120.205 E.04947
G1 X130.3 Y120.728 E.06595
G3 X132.316 Y122.214 I-7.24 J11.94 E.30004
G1 X132.783 Y121.892 E.06775
G1 X133.038 Y122.217 E.04947
G1 X132.628 Y122.585 E.06594
G3 X133.631 Y124.879 I-12.24 J6.72 E.30004
G1 X134.219 Y124.832 E.07059
G1 X134.279 Y125.24 E.04932
G1 X133.715 Y125.362 E.06909
G3 X133.437 Y127.845 I-13.934 J-.302 E.29938
G1 X133.949 Y128.088 E.06776
G1 X133.795 Y128.472 E.04947
G1 X133.272 Y128.3 E.06595
G3 X131.786 Y130.316 I-11.94 J-7.24 E.30004
G1 X132.108 Y130.783 E.06775
G1 X131.783 Y131.038 E.04947
G1 X131.415 Y130.628 E.06594
G3 X129.121 Y131.631 I-6.72 J-12.24 E.30004
G1 X129.166 Y132.196 E.06776
G1 X128.757 Y132.255 E.04947
G1 X128.644 Y131.715 E.06595
G3 X126.155 Y131.437 I.3 J-13.96 E.30004
G1 X125.912 Y131.949 E.06776
G1 X125.528 Y131.795 E.04947
G1 X125.7 Y131.272 E.06595
G3 X123.684 Y129.786 I7.24 J-11.94 E.30004
G1 X123.217 Y130.108 E.06776
G1 X122.962 Y129.783 E.04947
G1 X123.372 Y129.415 E.06595
G3 X122.373 Y127.134 I12.239 J-6.72 E.29839
G1 X121.875 Y127.897 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2409
G1 X121.796 Y127.903 E.00942
G3 X119.065 Y127.731 I-.893 J-7.593 E.32915
G1 X119.037 Y127.571 E.01952
G3 X118.959 Y127.038 I6.054 J-1.162 E.06437
G3 X121.585 Y126.04 I3.865 J6.215 E.33822
G3 X121.747 Y124.58 I9.975 J.367 E.17594
G1 X121.676 Y124.546 E.00942
G3 X119.397 Y123.032 I3.024 J-7.022 E.32915
G1 X119.453 Y122.879 E.01952
G3 X119.651 Y122.379 I5.825 J2.021 E.06437
G3 X122.424 Y122.827 I.26 J7.192 E.3383
G3 X123.295 Y121.644 I8.456 J5.306 E.17594
G1 X123.25 Y121.579 E.00942
G3 X122.033 Y119.128 I6.13 J-4.57 E.32915
G1 X122.159 Y119.023 E.01952
G3 X122.58 Y118.689 I4.034 J4.662 E.06437
G3 X124.758 Y120.465 I-3.371 J6.358 E.3383
G3 X126.103 Y119.875 I4.67 J8.822 E.17594
G1 X126.097 Y119.796 E.00942
G3 X126.269 Y117.065 I7.593 J-.893 E.32915
G1 X126.429 Y117.037 E.01952
G3 X126.962 Y116.959 I1.164 J6.063 E.06447
G3 X127.96 Y119.585 I-6.12 J3.827 E.33826
G3 X129.42 Y119.747 I-.367 J9.975 E.17594
G1 X129.454 Y119.676 E.00942
G3 X130.968 Y117.397 I7.022 J3.024 E.32915
G1 X131.121 Y117.453 E.01952
G3 X131.621 Y117.651 I-2.021 J5.825 E.06437
G3 X131.173 Y120.424 I-7.192 J.26 E.3383
G3 X132.356 Y121.295 I-5.306 J8.456 E.17594
G1 X132.421 Y121.25 E.00942
G3 X134.872 Y120.033 I4.57 J6.13 E.32915
G1 X134.977 Y120.159 E.01952
G3 X135.311 Y120.58 I-4.662 J4.033 E.06437
G3 X133.535 Y122.758 I-6.358 J-3.371 E.3383
G3 X134.125 Y124.103 I-8.823 J4.67 E.17594
G1 X134.204 Y124.097 E.00942
G3 X136.935 Y124.269 I.893 J7.593 E.32915
G1 X136.963 Y124.429 E.01952
G3 X137.041 Y124.962 I-6.053 J1.162 E.06437
G3 X134.415 Y125.962 I-3.886 J-6.257 E.33829
G3 X134.253 Y127.42 I-9.968 J-.368 E.17571
G1 X134.324 Y127.454 E.00942
G3 X136.603 Y128.968 I-3.024 J7.022 E.32915
G1 X136.547 Y129.121 E.01952
G3 X136.349 Y129.621 I-5.825 J-2.021 E.06437
G3 X133.576 Y129.173 I-.26 J-7.192 E.3383
G3 X132.705 Y130.356 I-8.456 J-5.306 E.17594
G1 X132.75 Y130.421 E.00942
G3 X133.967 Y132.872 I-6.13 J4.57 E.32915
G1 X133.841 Y132.977 E.01952
G3 X133.42 Y133.311 I-4.033 J-4.662 E.06437
G3 X131.242 Y131.535 I3.371 J-6.358 E.3383
G3 X129.897 Y132.125 I-4.67 J-8.823 E.17594
G1 X129.903 Y132.204 E.00942
G3 X129.731 Y134.935 I-7.593 J.893 E.32915
G1 X129.571 Y134.963 E.01952
G3 X129.038 Y135.041 I-1.162 J-6.053 E.06437
G3 X128.04 Y132.415 I6.215 J-3.865 E.33822
G3 X126.58 Y132.253 I.367 J-9.975 E.17594
G1 X126.546 Y132.324 E.00942
G3 X125.032 Y134.603 I-7.022 J-3.024 E.32915
G1 X124.879 Y134.547 E.01952
M73 P66 R3
G3 X124.379 Y134.349 I2.021 J-5.826 E.06437
G3 X124.827 Y131.576 I7.192 J-.26 E.3383
G3 X123.644 Y130.705 I5.306 J-8.456 E.17594
G1 X123.579 Y130.75 E.00942
G3 X121.128 Y131.967 I-4.57 J-6.13 E.32915
G1 X121.023 Y131.841 E.01952
G3 X120.689 Y131.42 I4.662 J-4.034 E.06437
G3 X122.465 Y129.242 I6.358 J3.371 E.3383
G3 X121.915 Y128.01 I8.823 J-4.67 E.16159
M204 S10000
; WIPE_START
G1 F24000
G1 X121.796 Y127.903 E-.22775
G1 X121.208 Y127.95 E-.84099
G1 X120.511 Y127.953 E-.99379
G1 X119.96 Y127.9 E-.78747
; WIPE_END
G1 E-.15 F1800
G1 X121.411 Y127.011 Z2.8 F30000
G1 Z2.4
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 1.08319
G1 F1804.791
G2 X120.856 Y127.1 I2.137 J15.134 E.09136
; LINE_WIDTH: 1.04711
G1 F1872.519
G1 X120.715 Y127.122 E.02231
; LINE_WIDTH: 0.998246
G1 F1972.807
G1 X120.574 Y127.143 E.02118
; LINE_WIDTH: 0.973814
G1 F2027.087
G1 X119.374 Y127.356 E.17646
G1 X119.372 Y127.343 F30000
; LINE_WIDTH: 0.836239
G1 F2398.727
G1 X121.409 Y126.996 E.2527
G1 X121.787 Y123.585 F30000
; LINE_WIDTH: 1.0818
G1 F1807.312
G2 X121.263 Y123.381 I-4.428 J10.605 E.09122
; LINE_WIDTH: 1.04711
G1 F1872.52
G1 X121.13 Y123.329 E.02231
; LINE_WIDTH: 0.998244
G1 F1972.812
G1 X120.998 Y123.277 E.02118
; LINE_WIDTH: 0.973811
G1 F2027.094
G1 X119.852 Y122.861 E.17646
G1 X119.854 Y122.854 F30000
; LINE_WIDTH: 0.839509
G1 F2388.319
G1 X121.797 Y123.56 E.25384
G1 X123.827 Y120.802 F30000
; LINE_WIDTH: 1.0818
G1 F1807.311
G2 X123.475 Y120.363 I-9.114 J6.95 E.09123
; LINE_WIDTH: 1.04711
G1 F1872.517
G1 X123.386 Y120.252 E.02231
; LINE_WIDTH: 0.998252
G1 F1972.795
G1 X123.297 Y120.141 E.02117
; LINE_WIDTH: 0.973821
G1 F2027.073
G1 X122.513 Y119.207 E.17647
G1 X122.518 Y119.203 F30000
; LINE_WIDTH: 0.839507
G1 F2388.325
G1 X123.848 Y120.785 E.25384
G1 X126.985 Y119.411 F30000
; LINE_WIDTH: 1.08179
G1 F1807.313
G2 X126.9 Y118.856 I-11.367 J1.462 E.09122
; LINE_WIDTH: 1.04712
G1 F1872.514
G1 X126.878 Y118.715 E.02231
; LINE_WIDTH: 0.998254
G1 F1972.791
G1 X126.857 Y118.574 E.02117
; LINE_WIDTH: 0.973823
G1 F2027.067
G1 X126.644 Y117.374 E.17647
G1 X126.651 Y117.373 F30000
; LINE_WIDTH: 0.839511
G1 F2388.313
G1 X127.011 Y119.408 E.25384
G1 X130.415 Y119.787 F30000
; LINE_WIDTH: 1.07655
G1 F1816.888
G2 X130.619 Y119.263 I-10.571 J-4.416 E.09075
; LINE_WIDTH: 1.04712
G1 F1872.512
G1 X130.671 Y119.13 E.02231
; LINE_WIDTH: 0.998255
G1 F1972.789
G1 X130.723 Y118.998 E.02117
; LINE_WIDTH: 0.968565
G1 F2039.141
G1 X131.139 Y117.85 E.17564
G1 X131.146 Y117.853 F30000
; LINE_WIDTH: 0.821205
G1 F2409
G1 X130.44 Y119.797 E.24788
G1 X133.198 Y121.827 F30000
; LINE_WIDTH: 1.07655
G1 F1816.887
G2 X133.637 Y121.475 I-6.956 J-9.12 E.09075
; LINE_WIDTH: 1.04712
G1 F1872.511
G1 X133.748 Y121.386 E.02231
; LINE_WIDTH: 0.998252
G1 F1972.795
G1 X133.859 Y121.297 E.02118
; LINE_WIDTH: 0.968565
G1 F2039.142
G1 X134.794 Y120.512 E.17564
G1 X134.798 Y120.517 F30000
; LINE_WIDTH: 0.821199
G1 F2409
G1 X133.215 Y121.848 E.24788
G1 X132.405 Y123.707 F30000
; LINE_WIDTH: 0.713798
G1 F2409
G1 X132.022 Y122.888 E.0925
G1 X131.978 Y122.83 E.00748
; LINE_WIDTH: 0.717778
G1 X131.597 Y122.496 E.05223
; LINE_WIDTH: 0.683896
G2 X130.297 Y121.535 I-4.682 J4.974 E.15792
; LINE_WIDTH: 0.722228
G1 X130.074 Y121.412 E.0264
; LINE_WIDTH: 0.764608
G1 X129.814 Y121.279 E.03228
; LINE_WIDTH: 0.755733
G1 X129.567 Y121.218 E.02782
; LINE_WIDTH: 0.715156
G2 X129.287 Y121.15 I-1.402 J5.157 E.02951
; LINE_WIDTH: 0.684279
G2 X127.678 Y120.985 I-1.511 J6.784 E.15818
; LINE_WIDTH: 0.729911
G1 X127.463 Y120.991 E.02256
; LINE_WIDTH: 0.768968
G2 X127.134 Y121.025 I-.074 J.879 E.03699
; LINE_WIDTH: 0.742496
G1 X126.89 Y121.098 E.02725
; LINE_WIDTH: 0.691263
G2 X126.167 Y121.341 I2.002 J7.146 E.0753
; LINE_WIDTH: 0.686823
G1 X126.137 Y121.352 E.00317
G2 X125.145 Y121.858 I3.288 J7.684 E.10915
; LINE_WIDTH: 0.738234
G1 X124.996 Y121.951 E.01864
; LINE_WIDTH: 0.768582
G2 X124.707 Y122.181 I.609 J1.063 E.04124
; LINE_WIDTH: 0.730512
G1 X124.534 Y122.367 E.02674
; LINE_WIDTH: 0.682863
G2 X123.693 Y123.441 I4.297 J4.227 E.13301
; LINE_WIDTH: 0.703243
G1 X123.434 Y123.879 E.05119
; LINE_WIDTH: 0.730674
G1 X123.417 Y123.91 E.00366
; LINE_WIDTH: 0.747208
G1 X123.355 Y124.03 E.01461
; LINE_WIDTH: 0.767746
G2 X123.228 Y124.381 I.768 J.476 E.04181
; LINE_WIDTH: 0.735647
G1 X123.219 Y124.415 E.00372
; LINE_WIDTH: 0.719784
G1 X123.164 Y124.664 E.02628
; LINE_WIDTH: 0.681477
G2 X122.989 Y126.016 I5.71 J1.43 E.1327
; LINE_WIDTH: 0.697142
G1 X122.988 Y126.271 E.02535
; LINE_WIDTH: 0.728053
G2 X122.988 Y126.561 I5.366 J.142 E.03036
; LINE_WIDTH: 0.761143
G2 X123.08 Y127.06 I1.229 J.033 E.05634
; LINE_WIDTH: 0.70075
G2 X123.246 Y127.577 I9.649 J-2.823 E.05443
; LINE_WIDTH: 0.679197
G2 X123.706 Y128.589 I5.744 J-1.999 E.10758
; LINE_WIDTH: 0.70468
G1 X123.834 Y128.809 E.02568
; LINE_WIDTH: 0.739922
G2 X123.982 Y129.059 I4.71 J-2.605 E.03101
; LINE_WIDTH: 0.756104
G1 X124.043 Y129.153 E.01222
G1 X124.327 Y129.433 E.04354
; LINE_WIDTH: 0.684864
G2 X125.643 Y130.43 I4.877 J-5.074 E.16156
; LINE_WIDTH: 0.713468
G1 X125.865 Y130.554 E.02606
; LINE_WIDTH: 0.753064
G2 X126.12 Y130.696 I2.748 J-4.645 E.03175
; LINE_WIDTH: 0.78005
G1 X126.149 Y130.71 E.00363
; LINE_WIDTH: 0.764521
G1 X126.381 Y130.769 E.02643
; LINE_WIDTH: 0.722773
G2 X126.645 Y130.835 I1.36 J-4.872 E.02827
; LINE_WIDTH: 0.683912
G2 X128.253 Y131.015 I1.562 J-6.67 E.15805
; LINE_WIDTH: 0.723103
G1 X128.502 Y131.01 E.02595
; LINE_WIDTH: 0.765441
G1 X128.798 Y130.993 E.03282
; LINE_WIDTH: 0.754094
G1 X129.043 Y130.922 E.02775
; LINE_WIDTH: 0.714024
G2 X129.319 Y130.841 I-1.367 J-5.16 E.02945
; LINE_WIDTH: 0.684378
G2 X130.795 Y130.178 I-2.095 J-6.637 E.15821
; LINE_WIDTH: 0.730868
G1 X130.974 Y130.067 E.0221
; LINE_WIDTH: 0.769136
G2 X131.244 Y129.869 I-.398 J-.826 E.0375
; LINE_WIDTH: 0.735577
G1 X131.475 Y129.624 E.03564
; LINE_WIDTH: 0.690987
G1 X131.706 Y129.379 E.0332
; LINE_WIDTH: 0.646397
G1 X131.937 Y129.135 E.03075
; LINE_WIDTH: 0.615373
G2 X132.06 Y128.977 I-.61 J-.605 E.0173
; LINE_WIDTH: 0.639851
G1 X132.099 Y128.884 E.00911
; LINE_WIDTH: 0.682653
G1 X132.12 Y128.819 E.00665
; LINE_WIDTH: 0.703375
G1 X132.23 Y128.453 E.03846
G1 X132.177 Y126.495 F30000
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.797471
G1 F2409
G1 X132.157 Y126.976 E.05588
; LINE_WIDTH: 0.746805
G2 X132.138 Y127.701 I9.076 J.603 E.07812
G1 X132.72 Y127.876 E.06548
; LINE_WIDTH: 0.759066
G1 X132.812 Y127.214 E.07326
; LINE_WIDTH: 0.79842
G2 X132.907 Y126.518 I-13.682 J-2.223 E.08158
; LINE_WIDTH: 0.844449
G1 F2372.765
G1 X132.964 Y125.335 E.14641
G1 X132.939 Y125.174 E.02021
G1 X132.652 Y124.421 E.09957
G1 X132.196 Y124.634 E.0623
G3 X132.179 Y126.375 I-54.223 J.338 E.21519
G1 X134.615 Y125 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 0.821948
G1 F2409
G1 X136.628 Y124.657 E.24497
G1 X136.626 Y124.644 F30000
; LINE_WIDTH: 0.968572
G1 F2039.125
G1 X135.426 Y124.857 E.17542
; LINE_WIDTH: 0.998253
G1 F1972.792
G1 X135.285 Y124.878 E.02118
; LINE_WIDTH: 1.04712
G1 F1872.514
G1 X135.144 Y124.9 E.02231
; LINE_WIDTH: 1.07866
G1 F1813.018
G3 X134.613 Y124.985 I-2.573 J-14.378 E.08702
G1 X134.213 Y128.415 F30000
; LINE_WIDTH: 1.07655
G1 F1816.875
G2 X134.737 Y128.619 I4.415 J-10.569 E.09074
; LINE_WIDTH: 1.04711
G1 F1872.519
G1 X134.87 Y128.671 E.02231
; LINE_WIDTH: 0.998244
G1 F1972.812
G1 X135.002 Y128.723 E.02118
; LINE_WIDTH: 0.968564
G1 F2039.145
G1 X136.148 Y129.139 E.17542
G1 X136.146 Y129.146 F30000
; LINE_WIDTH: 0.821196
G1 F2409
G1 X134.203 Y128.44 E.24767
G1 X132.173 Y131.198 F30000
; LINE_WIDTH: 1.07655
G1 F1816.887
G2 X132.525 Y131.637 I9.108 J-6.946 E.09075
; LINE_WIDTH: 1.04712
G1 F1872.513
G1 X132.614 Y131.748 E.02231
; LINE_WIDTH: 0.99825
G1 F1972.798
G1 X132.703 Y131.859 E.02118
; LINE_WIDTH: 0.968566
G1 F2039.139
G1 X133.487 Y132.793 E.17542
G1 X133.482 Y132.797 F30000
; LINE_WIDTH: 0.821179
G1 F2409
G1 X132.152 Y131.215 E.24767
G1 X129.011 Y132.589 F30000
; LINE_WIDTH: 1.08318
G1 F1804.793
G2 X129.1 Y133.144 I15.135 J-2.138 E.09135
; LINE_WIDTH: 1.04711
G1 F1872.516
G1 X129.122 Y133.285 E.02231
; LINE_WIDTH: 0.99825
G1 F1972.799
G1 X129.143 Y133.426 E.02118
; LINE_WIDTH: 0.973819
G1 F2027.077
G1 X129.356 Y134.626 E.17646
G1 X129.343 Y134.628 F30000
; LINE_WIDTH: 0.836235
G1 F2398.738
G1 X128.996 Y132.591 E.25269
G1 X125.585 Y132.213 F30000
; LINE_WIDTH: 1.0818
G1 F1807.305
G2 X125.381 Y132.737 I10.57 J4.415 E.09123
; LINE_WIDTH: 1.04711
G1 F1872.519
G1 X125.329 Y132.87 E.02231
; LINE_WIDTH: 0.998244
G1 F1972.812
G1 X125.277 Y133.002 E.02118
; LINE_WIDTH: 0.973811
G1 F2027.095
G1 X124.861 Y134.148 E.17646
G1 X124.854 Y134.146 F30000
; LINE_WIDTH: 0.839508
G1 F2388.322
G1 X125.56 Y132.203 E.25384
G1 X122.802 Y130.173 F30000
; LINE_WIDTH: 1.0818
G1 F1807.308
G2 X122.363 Y130.525 I6.958 J9.123 E.09123
; LINE_WIDTH: 1.04711
G1 F1872.518
G1 X122.252 Y130.614 E.02231
; LINE_WIDTH: 0.998251
G1 F1972.797
G1 X122.141 Y130.703 E.02118
; LINE_WIDTH: 0.973819
G1 F2027.077
G1 X121.207 Y131.487 E.17647
G1 X121.203 Y131.482 F30000
; LINE_WIDTH: 0.839506
G1 F2388.328
G1 X122.785 Y130.152 E.25384
; CHANGE_LAYER
; Z_HEIGHT: 2.8
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X121.254 Y131.439 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 7/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L7
M991 S0 P6 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z2.8 I.771 J.942 P1  F30000
G1 X131.343 Y123.182 Z2.8
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2451.784
G1 X131.444 Y123.276 E.01653
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X127.963 Y121.661 I-2.777 J-3.338 E1.9877
G3 X130.78 Y122.66 I.029 J4.388 E.36493
G1 X131.255 Y123.1 E.0775
G1 X130.71 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X127.968 Y122.395 I-2.307 J-2.773 E1.65128
G1 X128.17 Y122.393 E.02411
G3 X130.627 Y123.509 I-.217 J3.743 E.33037
M204 S10000
; WIPE_START
G1 F24000
G1 X130.661 Y125.509 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.196 Y127.097 Z3.2 F30000
G1 X122.287 Y127.29 Z3.2
G1 Z2.8
G1 E3 F1800
; FEATURE: Inner wall
G1 F2451.784
G1 X121.767 Y127.346 E.06254
G1 X121.694 Y126.943 E.04897
G1 X122.299 Y126.786 E.07488
G3 X122.502 Y124.302 I16.747 J.114 E.29842
G1 X121.929 Y124.049 E.07489
G1 X122.067 Y123.664 E.04897
G1 X122.67 Y123.83 E.07488
G3 X124.087 Y121.781 I14.448 J8.473 E.29842
G1 X123.718 Y121.275 E.07489
G1 X124.03 Y121.01 E.04897
G1 X124.469 Y121.456 E.07488
G3 X126.721 Y120.389 I8.275 J14.561 E.29842
G1 X126.654 Y119.767 E.07488
G1 X127.057 Y119.694 E.04897
G1 X127.214 Y120.299 E.07488
G3 X129.698 Y120.502 I-.114 J16.747 E.29842
G1 X129.951 Y119.929 E.07489
G1 X130.336 Y120.067 E.04897
G1 X130.17 Y120.67 E.07488
G3 X132.219 Y122.087 I-8.472 J14.447 E.29842
G1 X132.725 Y121.718 E.07488
G1 X132.99 Y122.03 E.04897
G1 X132.544 Y122.469 E.07488
G3 X133.611 Y124.721 I-14.561 J8.276 E.29842
G1 X134.233 Y124.654 E.07488
G1 X134.306 Y125.057 E.04897
G1 X133.701 Y125.214 E.07488
G3 X133.498 Y127.698 I-16.747 J-.114 E.29842
G1 X134.071 Y127.951 E.07489
G1 X133.933 Y128.336 E.04897
G1 X133.33 Y128.17 E.07488
G3 X131.913 Y130.219 I-14.447 J-8.472 E.29842
G1 X132.282 Y130.725 E.07489
G1 X131.97 Y130.99 E.04897
G1 X131.531 Y130.544 E.07488
G3 X129.279 Y131.611 I-8.276 J-14.561 E.29842
G1 X129.346 Y132.233 E.07488
G1 X128.943 Y132.306 E.04897
G1 X128.786 Y131.701 E.07488
G3 X126.302 Y131.498 I.114 J-16.747 E.29842
M73 P67 R3
G1 X126.049 Y132.071 E.07489
G1 X125.664 Y131.933 E.04897
G1 X125.83 Y131.33 E.07488
G3 X123.781 Y129.913 I8.473 J-14.448 E.29842
G1 X123.275 Y130.282 E.07489
G1 X123.01 Y129.97 E.04897
G1 X123.456 Y129.531 E.07488
G3 X122.395 Y127.295 I14.561 J-8.275 E.29642
G1 X121.925 Y128.067 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X121.855 Y128.075 E.00845
G3 X119.12 Y127.978 I-1.102 J-7.535 E.32923
G1 X119.084 Y127.82 E.0194
G3 X118.992 Y127.289 I10.917 J-2.165 E.06445
G3 X121.586 Y126.213 I4.195 J6.447 E.33797
G3 X121.705 Y124.753 I11.719 J.219 E.17537
G1 X121.64 Y124.724 E.00845
G3 X119.32 Y123.273 I2.813 J-7.076 E.32923
G1 X119.368 Y123.118 E.0194
G3 X119.554 Y122.612 I10.54 J3.585 E.06445
G3 X122.339 Y122.977 I.41 J7.681 E.33797
G3 X123.172 Y121.772 I10.041 J6.05 E.17537
G1 X123.13 Y121.715 E.00845
G3 X121.847 Y119.298 I5.974 J-4.722 E.32923
G1 X121.966 Y119.188 E.0194
G3 X122.38 Y118.843 I7.336 J8.375 E.06445
G3 X124.609 Y120.552 I-3.486 J6.857 E.33797
G3 X125.933 Y119.925 I5.67 J10.26 E.17537
G1 X125.925 Y119.855 E.00845
G3 X126.022 Y117.12 I7.535 J-1.102 E.32923
G1 X126.18 Y117.084 E.0194
G3 X126.712 Y116.992 I2.16 J10.891 E.06455
G3 X127.787 Y119.586 I-6.476 J4.205 E.33793
G3 X129.247 Y119.705 I-.22 J11.72 E.17537
G1 X129.276 Y119.64 E.00845
G3 X130.727 Y117.32 I7.076 J2.813 E.32923
G1 X130.882 Y117.368 E.0194
G3 X131.388 Y117.554 I-3.585 J10.539 E.06445
G3 X131.023 Y120.339 I-7.681 J.41 E.33797
G3 X132.228 Y121.172 I-6.05 J10.04 E.17537
G1 X132.285 Y121.13 E.00845
G3 X134.702 Y119.847 I4.722 J5.974 E.32923
G1 X134.812 Y119.966 E.0194
G3 X135.157 Y120.38 I-8.375 J7.336 E.06445
G3 X133.448 Y122.609 I-6.857 J-3.486 E.33797
G3 X134.075 Y123.933 I-10.26 J5.67 E.17537
G1 X134.145 Y123.925 E.00845
G3 X136.88 Y124.022 I1.102 J7.535 E.32923
G1 X136.916 Y124.18 E.0194
G3 X137.008 Y124.711 I-10.918 J2.165 E.06445
G3 X134.414 Y125.787 I-4.195 J-6.447 E.33797
G3 X134.295 Y127.247 I-11.719 J-.219 E.17537
G1 X134.36 Y127.276 E.00845
G3 X136.68 Y128.727 I-2.813 J7.076 E.32923
G1 X136.632 Y128.882 E.0194
G3 X136.446 Y129.388 I-10.539 J-3.584 E.06445
G3 X133.661 Y129.023 I-.41 J-7.681 E.33797
G3 X132.828 Y130.228 I-10.041 J-6.051 E.17537
G1 X132.87 Y130.285 E.00845
G3 X134.153 Y132.702 I-5.974 J4.722 E.32923
G1 X134.034 Y132.812 E.0194
G3 X133.62 Y133.157 I-7.334 J-8.373 E.06445
G3 X131.391 Y131.448 I3.485 J-6.857 E.33797
G3 X130.067 Y132.075 I-5.67 J-10.26 E.17537
G1 X130.075 Y132.145 E.00845
G3 X129.978 Y134.88 I-7.535 J1.102 E.32923
G1 X129.82 Y134.916 E.0194
G3 X129.289 Y135.008 I-2.165 J-10.916 E.06445
G3 X128.213 Y132.414 I6.447 J-4.195 E.33797
G3 X126.753 Y132.295 I.219 J-11.719 E.17537
G1 X126.724 Y132.36 E.00845
G3 X125.273 Y134.68 I-7.076 J-2.813 E.32923
G1 X125.118 Y134.632 E.0194
G3 X124.612 Y134.446 I3.585 J-10.54 E.06445
G3 X124.977 Y131.661 I7.681 J-.41 E.33797
G3 X123.772 Y130.828 I6.051 J-10.041 E.17537
G1 X123.715 Y130.87 E.00845
G3 X121.298 Y132.153 I-4.722 J-5.974 E.32923
G1 X121.188 Y132.034 E.0194
G3 X120.843 Y131.62 I8.374 J-7.335 E.06445
G3 X122.552 Y129.391 I6.857 J3.486 E.33797
G3 X121.97 Y128.178 I10.26 J-5.67 E.16102
M204 S10000
; WIPE_START
G1 F24000
G1 X121.855 Y128.075 E-.22089
G1 X121.265 Y128.138 E-.84438
G1 X120.568 Y128.16 E-.9939
G1 X120.015 Y128.122 E-.79083
; WIPE_END
G1 E-.15 F1800
G1 X121.369 Y127.212 Z3.2 F30000
G1 Z2.8
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 1.04572
G1 F1875.232
G1 X120.99 Y127.28 E.06039
; LINE_WIDTH: 0.99766
G1 F1974.075
G1 X120.61 Y127.349 E.05737
; LINE_WIDTH: 0.97363
G1 F2027.508
G1 X119.414 Y127.595 E.1766
G1 X121.365 Y127.186 F30000
; LINE_WIDTH: 0.839312
G1 F2388.943
G1 X119.413 Y127.588 E.24471
G1 X119.412 Y127.581 F30000
; LINE_WIDTH: 0.666387
G1 F3000
G1 X121.364 Y127.179 E.18854
G1 X121.663 Y123.703 F30000
; LINE_WIDTH: 0.666374
G1 F3000
G1 X119.772 Y123.075 E.18854
G1 X119.77 Y123.082 F30000
; LINE_WIDTH: 0.839316
G1 F2388.93
G1 X121.661 Y123.71 E.2447
G1 X121.652 Y123.734 F30000
; LINE_WIDTH: 1.04572
G1 F1875.244
G1 X121.289 Y123.603 E.06039
; LINE_WIDTH: 0.997654
G1 F1974.087
G1 X120.925 Y123.473 E.05737
; LINE_WIDTH: 0.973623
G1 F2027.525
G1 X119.767 Y123.089 E.17659
; WIPE_START
G1 F24000
G1 X120.925 Y123.473 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X122.326 Y119.362 Z3.2 F30000
G1 Z2.8
G1 E3 F1800
; LINE_WIDTH: 0.973628
G1 F2027.513
G1 X123.137 Y120.274 E.1766
; LINE_WIDTH: 0.997658
G1 F1974.079
G1 X123.386 Y120.569 E.05737
; LINE_WIDTH: 1.04572
G1 F1875.238
G1 X123.636 Y120.864 E.06039
G1 X123.655 Y120.847 F30000
; LINE_WIDTH: 0.839323
G1 F2388.908
G1 X122.331 Y119.357 E.24471
G1 X122.337 Y119.353 F30000
; LINE_WIDTH: 0.666384
G1 F3000
G1 X123.661 Y120.842 E.18854
; WIPE_START
G1 F24000
G1 X122.337 Y119.353 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X126.405 Y117.414 Z3.2 F30000
G1 Z2.8
G1 E3 F1800
; LINE_WIDTH: 0.97363
G1 F2027.508
G1 X126.651 Y118.61 E.1766
; LINE_WIDTH: 0.99766
G1 F1974.076
G1 X126.72 Y118.99 E.05737
; LINE_WIDTH: 1.04572
G1 F1875.232
G1 X126.788 Y119.369 E.06039
G1 X126.814 Y119.365 F30000
; LINE_WIDTH: 0.839314
G1 F2388.936
G1 X126.412 Y117.413 E.24471
G1 X126.419 Y117.412 F30000
; LINE_WIDTH: 0.666399
G1 F3000
G1 X126.821 Y119.364 E.18855
G1 X130.29 Y119.661 F30000
; LINE_WIDTH: 0.821018
G1 F2448.39
G1 X130.918 Y117.77 E.23876
G1 X130.925 Y117.772 F30000
; LINE_WIDTH: 0.649867
G1 F3000
G1 X130.297 Y119.663 E.18317
G1 X130.79 Y119.803 F30000
; LINE_WIDTH: 1.06183
G1 F1844.283
G1 X130.432 Y119.189 E.11303
G1 X130.48 Y119.057 E.02228
; LINE_WIDTH: 0.997652
G1 F1974.092
G1 X130.527 Y118.925 E.02081
; LINE_WIDTH: 0.968366
G1 F2039.602
G1 X130.911 Y117.767 E.17555
; WIPE_START
G1 F24000
G1 X130.527 Y118.925 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X134.638 Y120.326 Z3.2 F30000
G1 Z2.8
G1 E3 F1800
; LINE_WIDTH: 0.968376
G1 F2039.578
G1 X133.726 Y121.137 E.17555
; LINE_WIDTH: 0.997657
G1 F1974.083
G1 X133.619 Y121.227 E.02082
; LINE_WIDTH: 1.06182
G1 F1844.303
G1 X133.512 Y121.318 E.02228
G1 X132.813 Y121.199 E.11271
G1 X133.153 Y121.655 F30000
; LINE_WIDTH: 0.821022
G1 F2448.376
G1 X134.643 Y120.331 E.23877
G1 X134.647 Y120.337 F30000
; LINE_WIDTH: 0.649866
G1 F3000
G1 X133.158 Y121.661 E.18318
G1 X132.401 Y123.702 F30000
; LINE_WIDTH: 0.694433
G1 F2957.647
G1 X132.015 Y122.896 E.08863
; LINE_WIDTH: 0.704809
G1 F2908.064
G1 X131.944 Y122.803 E.01181
; LINE_WIDTH: 0.724141
G1 F2819.99
G1 X131.873 Y122.71 E.01218
G1 X131.217 Y122.16 E.08904
; LINE_WIDTH: 0.679633
G1 F3000
G2 X130.295 Y121.54 I-4.074 J5.064 E.10768
; LINE_WIDTH: 0.708791
G1 F2889.475
G1 X130.07 Y121.419 E.02585
; LINE_WIDTH: 0.746149
G1 F2725.999
G2 X129.813 Y121.282 I-2.66 J4.686 E.03136
; LINE_WIDTH: 0.76553
G1 F2648.268
G1 X129.703 Y121.231 E.01344
G1 X129.323 Y121.146 E.04315
; LINE_WIDTH: 0.687818
G1 F2990.146
G2 X128.251 Y121 I-1.706 J8.524 E.10623
; LINE_WIDTH: 0.684432
G1 F3000
G1 X128.238 Y120.999 E.00125
G2 X127.678 Y120.991 I-1.226 J66.649 E.05463
; LINE_WIDTH: 0.718185
G1 F2846.551
G1 X127.424 Y121.001 E.02626
; LINE_WIDTH: 0.759904
G1 F2670.372
G2 X127.132 Y121.013 I.082 J5.407 E.03213
; LINE_WIDTH: 0.789391
G1 F2558.451
G1 X127.09 Y121.017 E.00475
; LINE_WIDTH: 0.774166
G1 F2615.042
G1 X126.867 Y121.088 E.0263
; LINE_WIDTH: 0.730139
G1 F2793.739
G2 X126.612 Y121.171 I1.41 J4.777 E.02816
; LINE_WIDTH: 0.685446
G1 F3000
G2 X125.149 Y121.863 I2.369 J6.9 E.15849
; LINE_WIDTH: 0.728824
G1 F2799.45
G1 X124.935 Y122.001 E.0267
; LINE_WIDTH: 0.773798
G1 F2616.443
M73 P68 R3
G1 X124.694 Y122.166 E.03276
; LINE_WIDTH: 0.764282
G1 F2653.141
G1 X124.524 Y122.357 E.02818
; LINE_WIDTH: 0.72094
G1 F2834.201
G2 X124.333 Y122.572 I3.903 J3.655 E.02982
; LINE_WIDTH: 0.685866
G1 F2999.871
G2 X123.425 Y123.913 I5.635 J4.794 E.15864
; LINE_WIDTH: 0.737084
G1 F2763.943
G1 X123.328 Y124.105 E.02283
; LINE_WIDTH: 0.778355
G1 F2599.223
G2 X123.202 Y124.41 I.705 J.468 E.03756
; LINE_WIDTH: 0.750234
G1 F2709.239
G1 X123.152 Y124.66 E.02758
; LINE_WIDTH: 0.711187
G1 F2878.405
G2 X123.097 Y124.942 I5.21 J1.172 E.0293
; LINE_WIDTH: 0.67978
G1 F3000
G2 X122.991 Y126.016 I6.49 J1.178 E.10454
; LINE_WIDTH: 0.700302
G1 F2929.396
G1 X122.996 Y126.525 E.05094
; LINE_WIDTH: 0.72603
G1 F2811.667
G1 X122.997 Y126.559 E.00361
; LINE_WIDTH: 0.745983
G1 F2726.686
G1 X123.008 Y126.734 E.01887
; LINE_WIDTH: 0.777912
G1 F2600.889
G2 X123.074 Y127.098 I1.173 J-.026 E.04186
; LINE_WIDTH: 0.737448
G1 F2762.401
G1 X123.157 Y127.338 E.02703
; LINE_WIDTH: 0.684014
G1 F3000
G2 X123.709 Y128.587 I6.087 J-1.943 E.1333
; LINE_WIDTH: 0.6945
G1 F2957.321
G1 X123.84 Y128.805 E.02524
; LINE_WIDTH: 0.723712
G1 F2821.886
G2 X123.989 Y129.053 I4.664 J-2.646 E.03012
; LINE_WIDTH: 0.755532
G1 F2687.806
G1 X124.065 Y129.165 E.0148
; LINE_WIDTH: 0.77701
G1 F2604.284
G2 X124.315 Y129.443 I.752 J-.425 E.0424
; LINE_WIDTH: 0.743281
G1 F2737.892
G1 X124.341 Y129.467 E.00381
; LINE_WIDTH: 0.725918
G1 F2812.159
G1 X124.535 Y129.632 E.02654
; LINE_WIDTH: 0.682489
G1 F3000
G2 X125.645 Y130.425 I4.187 J-4.681 E.13295
; LINE_WIDTH: 0.701547
G1 F2923.474
G1 X125.868 Y130.547 E.02554
; LINE_WIDTH: 0.735081
G1 F2772.47
G2 X126.124 Y130.686 I2.688 J-4.659 E.03075
; LINE_WIDTH: 0.770056
G1 F2630.749
G2 X126.608 Y130.841 I.591 J-1.016 E.05712
; LINE_WIDTH: 0.730657
G1 F2791.491
G1 X126.642 Y130.848 E.00366
; LINE_WIDTH: 0.70323
G1 F2915.503
G1 X127.143 Y130.936 E.05119
; LINE_WIDTH: 0.679742
G1 F3000
G2 X128.252 Y131.01 I.991 J-6.471 E.1077
; LINE_WIDTH: 0.70984
G1 F2884.617
G1 X128.507 Y131.002 E.0259
; LINE_WIDTH: 0.747717
G1 F2719.542
G2 X128.798 Y130.992 I-.044 J-5.394 E.03145
; LINE_WIDTH: 0.764675
G1 F2651.604
G1 X128.909 Y130.982 E.01237
G1 X129.29 Y130.863 E.04413
; LINE_WIDTH: 0.686518
G1 F2996.615
G2 X130.791 Y130.172 I-2.357 J-7.105 E.16208
; LINE_WIDTH: 0.719385
G1 F2841.158
G1 X131.007 Y130.036 E.02631
; LINE_WIDTH: 0.761626
G1 F2663.567
G2 X131.253 Y129.879 I-2.781 J-4.643 E.03222
; LINE_WIDTH: 0.790195
G1 F2555.531
G1 X131.279 Y129.861 E.00366
; LINE_WIDTH: 0.771365
G1 F2625.728
G1 X131.457 Y129.665 E.02956
; LINE_WIDTH: 0.725387
G1 F2814.498
G1 X131.635 Y129.469 E.02757
; LINE_WIDTH: 0.679408
G1 F3000
G1 X131.812 Y129.273 E.02559
; LINE_WIDTH: 0.627515
G2 X132.045 Y129.003 I-1.403 J-1.449 E.03153
; LINE_WIDTH: 0.623405
G1 X132.072 Y128.943 E.0057
; LINE_WIDTH: 0.648767
G1 X132.099 Y128.884 E.00597
; LINE_WIDTH: 0.661449
G1 X132.246 Y128.425 E.04521
G1 X132.18 Y126.371 F30000
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.806734
G1 F2496.901
G1 X132.164 Y126.89 E.061
; LINE_WIDTH: 0.764227
G1 F2653.354
G2 X132.148 Y127.654 I12.618 J.642 E.08457
G1 X132.709 Y127.834 E.06511
G2 X132.819 Y127.449 I-.451 J-.338 E.04528
; LINE_WIDTH: 0.775308
G1 F2610.711
G1 X132.866 Y126.932 E.05834
; LINE_WIDTH: 0.807572
G1 F2494.003
G2 X132.916 Y126.386 I-28.9 J-2.889 E.06451
; LINE_WIDTH: 0.840278
G1 F2385.883
G1 X132.953 Y125.181 E.14823
G1 X132.923 Y125.016 E.02063
G1 X132.663 Y124.406 E.08155
G1 X132.192 Y124.631 E.06425
G3 X132.181 Y126.251 I-77.902 J.267 E.19912
G1 X134.636 Y124.821 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 0.649876
G1 F3000
G1 X136.588 Y124.419 E.18318
G1 X136.587 Y124.412 F30000
; LINE_WIDTH: 0.82101
G1 F2448.415
G1 X134.635 Y124.814 E.23876
G1 X134.569 Y124.249 F30000
; LINE_WIDTH: 1.06182
G1 F1844.303
G1 X135.115 Y124.701 E.1127
G1 X135.252 Y124.676 E.02228
; LINE_WIDTH: 0.997658
G1 F1974.079
G1 X135.39 Y124.651 E.02081
; LINE_WIDTH: 0.968377
G1 F2039.577
G1 X136.586 Y124.405 E.17555
; WIPE_START
G1 F24000
G1 X135.39 Y124.651 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X136.233 Y128.911 Z3.2 F30000
G1 Z2.8
G1 E3 F1800
; LINE_WIDTH: 0.968378
G1 F2039.575
G1 X135.075 Y128.527 E.17555
; LINE_WIDTH: 0.997659
G1 F1974.077
G1 X134.943 Y128.48 E.02081
; LINE_WIDTH: 1.06182
G1 F1844.308
G1 X134.811 Y128.432 E.02228
G1 X134.565 Y127.768 E.1127
G1 X134.339 Y128.29 F30000
; LINE_WIDTH: 0.821014
G1 F2448.402
G1 X136.23 Y128.918 E.23876
G1 X136.228 Y128.925 F30000
; LINE_WIDTH: 0.649868
G1 F3000
G1 X134.337 Y128.297 E.18318
G1 X132.339 Y131.158 F30000
; LINE_WIDTH: 0.649877
G1 F3000
G1 X133.663 Y132.647 E.18318
G1 X133.669 Y132.643 F30000
; LINE_WIDTH: 0.821019
G1 F2448.384
G1 X132.345 Y131.153 E.23876
G1 X132.801 Y130.813 F30000
; LINE_WIDTH: 1.06182
G1 F1844.309
G1 X132.682 Y131.512 E.11271
G1 X132.773 Y131.619 E.02228
; LINE_WIDTH: 0.997646
G1 F1974.106
G1 X132.863 Y131.726 E.02082
; LINE_WIDTH: 0.968365
G1 F2039.603
G1 X133.674 Y132.638 E.17554
; WIPE_START
G1 F24000
G1 X132.863 Y131.726 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X129.595 Y134.586 Z3.2 F30000
G1 Z2.8
G1 E3 F1800
; LINE_WIDTH: 0.968378
G1 F2039.575
G1 X129.349 Y133.39 E.17555
; LINE_WIDTH: 0.997662
G1 F1974.072
G1 X129.324 Y133.252 E.02081
; LINE_WIDTH: 1.06182
G1 F1844.305
G1 X129.299 Y133.115 E.02228
G1 X129.751 Y132.569 E.11269
G1 X129.186 Y132.635 F30000
; LINE_WIDTH: 0.839312
G1 F2388.942
G1 X129.588 Y134.587 E.24471
G1 X129.581 Y134.588 F30000
; LINE_WIDTH: 0.666387
G1 F3000
G1 X129.179 Y132.636 E.18854
; WIPE_START
G1 F24000
G1 X129.581 Y134.588 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X125.089 Y134.233 Z3.2 F30000
G1 Z2.8
G1 E3 F1800
; LINE_WIDTH: 0.97363
G1 F2027.508
G1 X125.473 Y133.075 E.1766
; LINE_WIDTH: 0.99766
G1 F1974.076
G1 X125.603 Y132.711 E.05737
; LINE_WIDTH: 1.04572
G1 F1875.235
G1 X125.734 Y132.348 E.06039
G1 X125.71 Y132.339 F30000
; LINE_WIDTH: 0.839315
G1 F2388.932
G1 X125.082 Y134.23 E.24471
G1 X125.075 Y134.228 F30000
; LINE_WIDTH: 0.666378
G1 F3000
G1 X125.703 Y132.337 E.18854
G1 X122.842 Y130.339 F30000
; LINE_WIDTH: 0.666404
G1 F3000
G1 X121.353 Y131.663 E.18855
G1 X121.357 Y131.669 F30000
; LINE_WIDTH: 0.839328
G1 F2388.893
G1 X122.847 Y130.345 E.24471
G1 X122.864 Y130.364 F30000
; LINE_WIDTH: 1.04572
G1 F1875.243
G1 X122.569 Y130.614 E.06039
; LINE_WIDTH: 0.997648
G1 F1974.102
G1 X122.274 Y130.863 E.05737
; LINE_WIDTH: 0.973616
G1 F2027.54
G1 X121.362 Y131.674 E.17659
; CHANGE_LAYER
; Z_HEIGHT: 3.2
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X122.274 Y130.863 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 8/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L8
M991 S0 P7 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z3.2 I.787 J.929 P1  F30000
G1 X131.343 Y123.182 Z3.2
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2451.784
G1 X131.444 Y123.276 E.01649
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X128.933 Y130.238 I-2.814 J-3.439 E.24795
G1 X128.933 Y130.238 E0
G3 X127.936 Y121.661 I-.933 J-4.238 E1.73602
G3 X130.78 Y122.66 I.057 J4.389 E.36823
G1 X131.255 Y123.101 E.07753
G1 X130.71 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X127.941 Y122.395 I-2.309 J-2.773 E1.64871
G1 X128.17 Y122.393 E.02741
G3 X130.627 Y123.509 I-.217 J3.743 E.33037
M204 S10000
; WIPE_START
G1 F24000
G1 X130.661 Y125.509 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.227 Y127.24 Z3.6 F30000
G1 X122.34 Y127.446 Z3.6
G1 Z3.2
G1 E3 F1800
; FEATURE: Inner wall
G1 F2451.784
G1 X121.806 Y127.519 E.06451
G1 X121.721 Y127.118 E.04895
G1 X122.322 Y126.944 E.07486
G3 X122.478 Y124.465 I14.016 J-.364 E.29764
G1 X121.877 Y124.218 E.07778
G1 X122.003 Y123.829 E.04895
G1 X122.611 Y123.979 E.07486
G3 X123.986 Y121.909 I12.323 J6.694 E.29764
G1 X123.588 Y121.395 E.07778
G1 X123.892 Y121.122 E.04895
G1 X124.344 Y121.555 E.07487
G3 X126.569 Y120.45 I7.323 J11.956 E.29764
G1 X126.481 Y119.806 E.07778
G1 X126.882 Y119.721 E.04895
G1 X127.056 Y120.322 E.07486
G3 X129.535 Y120.478 I.364 J14.016 E.29764
G1 X129.782 Y119.877 E.07778
G1 X130.171 Y120.003 E.04895
G1 X130.021 Y120.611 E.07486
G3 X132.091 Y121.986 I-6.694 J12.323 E.29764
G1 X132.605 Y121.588 E.07778
G1 X132.878 Y121.892 E.04895
G1 X132.445 Y122.344 E.07486
G3 X133.55 Y124.569 I-11.956 J7.323 E.29764
G1 X134.194 Y124.481 E.07778
G1 X134.279 Y124.882 E.04895
G1 X133.678 Y125.056 E.07486
G3 X133.522 Y127.535 I-14.016 J.364 E.29764
G1 X134.123 Y127.782 E.07778
G1 X133.997 Y128.171 E.04895
G1 X133.389 Y128.021 E.07486
G3 X132.014 Y130.091 I-12.323 J-6.694 E.29764
G1 X132.412 Y130.605 E.07778
G1 X132.108 Y130.878 E.04895
G1 X131.656 Y130.445 E.07486
G3 X129.431 Y131.55 I-7.323 J-11.956 E.29764
G1 X129.519 Y132.194 E.07778
G1 X129.118 Y132.279 E.04895
G1 X128.944 Y131.678 E.07486
G3 X126.465 Y131.522 I-.364 J-14.016 E.29764
G1 X126.218 Y132.123 E.07778
G1 X125.829 Y131.997 E.04895
G1 X125.979 Y131.389 E.07486
G3 X123.909 Y130.014 I6.694 J-12.323 E.29764
G1 X123.395 Y130.412 E.07778
G1 X123.122 Y130.108 E.04895
G1 X123.555 Y129.656 E.07486
G3 X122.453 Y127.44 I11.956 J-7.323 E.29656
G1 X121.993 Y128.234 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X121.912 Y128.245 E.0098
G3 X119.175 Y128.223 I-1.307 J-7.501 E.32919
G3 X119.138 Y128.066 I1.785 J-.513 E.01937
G3 X119.031 Y127.537 I5.996 J-1.479 E.06447
G3 X121.594 Y126.391 I4.235 J6.029 E.338
G3 X121.681 Y124.931 I10.799 J-.093 E.17507
G1 X121.605 Y124.9 E.0098
G3 X119.246 Y123.513 I2.618 J-7.15 E.32919
G3 X119.292 Y123.358 I1.803 J.448 E.01937
G3 X119.464 Y122.848 I5.917 J1.712 E.06432
G3 X122.257 Y123.135 I.623 J7.673 E.33786
G3 X123.062 Y121.915 I9.401 J5.32 E.17507
G1 X123.012 Y121.85 E.0098
G3 X121.663 Y119.469 I5.842 J-4.883 E.32919
G3 X121.78 Y119.358 I1.337 J1.289 E.01937
G3 X122.183 Y119.003 I4.269 J4.442 E.06432
G3 X124.459 Y120.648 I-3.297 J6.956 E.33786
G3 X125.766 Y119.993 I5.48 J9.305 E.17507
G1 X125.755 Y119.912 E.0098
G3 X125.777 Y117.175 I7.501 J-1.307 E.32919
G3 X125.934 Y117.138 I.513 J1.785 E.01937
G3 X126.461 Y117.032 I1.476 J5.981 E.06432
G3 X127.609 Y119.594 I-6.333 J4.375 E.33786
G3 X129.069 Y119.681 I.093 J10.799 E.17507
G1 X129.1 Y119.605 E.0098
G3 X130.487 Y117.246 I7.15 J2.618 E.32919
G3 X130.642 Y117.292 I-.448 J1.802 E.01937
G3 X131.152 Y117.464 I-1.712 J5.918 E.06432
G3 X130.865 Y120.257 I-7.673 J.623 E.33786
G3 X132.085 Y121.062 I-5.32 J9.401 E.17507
G1 X132.15 Y121.012 E.0098
G3 X134.531 Y119.663 I4.883 J5.842 E.32919
G3 X134.642 Y119.78 I-1.29 J1.337 E.01937
G3 X134.997 Y120.183 I-4.442 J4.269 E.06432
G3 X133.352 Y122.459 I-6.956 J-3.297 E.33786
G3 X134.007 Y123.766 I-9.305 J5.48 E.17507
G1 X134.088 Y123.755 E.0098
G3 X136.825 Y123.777 I1.307 J7.501 E.32919
G3 X136.862 Y123.934 I-1.785 J.513 E.01937
G3 X136.969 Y124.463 I-5.995 J1.479 E.06447
G3 X134.406 Y125.609 I-4.235 J-6.029 E.338
G3 X134.319 Y127.069 I-10.799 J.093 E.17507
G1 X134.395 Y127.1 E.0098
G3 X136.754 Y128.487 I-2.618 J7.15 E.32919
G3 X136.708 Y128.642 I-1.803 J-.448 E.01937
G3 X136.536 Y129.152 I-5.917 J-1.712 E.06432
G3 X133.743 Y128.865 I-.623 J-7.673 E.33786
G3 X132.938 Y130.085 I-9.401 J-5.32 E.17507
G1 X132.988 Y130.15 E.0098
G3 X134.337 Y132.531 I-5.842 J4.883 E.32919
G3 X134.22 Y132.642 I-1.337 J-1.29 E.01937
G3 X133.817 Y132.997 I-4.269 J-4.442 E.06432
G3 X131.541 Y131.352 I3.297 J-6.956 E.33786
G3 X130.234 Y132.007 I-5.48 J-9.305 E.17507
G1 X130.245 Y132.088 E.0098
M73 P69 R3
G3 X130.223 Y134.825 I-7.501 J1.307 E.32919
G3 X130.066 Y134.862 I-.513 J-1.785 E.01937
G3 X129.537 Y134.969 I-1.479 J-5.996 E.06447
G3 X128.391 Y132.406 I6.029 J-4.235 E.338
G3 X126.931 Y132.319 I-.093 J-10.799 E.17507
G1 X126.9 Y132.395 E.0098
G3 X125.513 Y134.754 I-7.15 J-2.618 E.32919
G3 X125.358 Y134.708 I.448 J-1.802 E.01937
G3 X124.848 Y134.536 I1.712 J-5.917 E.06432
G3 X125.135 Y131.743 I7.673 J-.623 E.33786
G3 X123.915 Y130.938 I5.32 J-9.401 E.17507
G1 X123.85 Y130.988 E.0098
G3 X121.469 Y132.337 I-4.883 J-5.842 E.32919
G3 X121.358 Y132.22 I1.289 J-1.337 E.01937
G3 X121.003 Y131.817 I4.442 J-4.269 E.06432
G3 X122.648 Y129.541 I6.956 J3.297 E.33786
G3 X122.04 Y128.344 I9.305 J-5.48 E.16071
M204 S10000
G1 X121.481 Y127.933 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 1.06119
G1 F1845.494
G1 X120.924 Y127.497 E.11246
G1 X120.799 Y127.521 E.0203
; LINE_WIDTH: 1.01092
G1 F1945.771
G1 X120.129 Y127.67 E.10346
; LINE_WIDTH: 0.994519
G1 F1980.9
G1 X119.459 Y127.819 E.10162
; WIPE_START
G1 F24000
G1 X120.129 Y127.67 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X119.69 Y123.319 Z3.6 F30000
G1 Z3.2
G1 E3 F1800
; LINE_WIDTH: 0.973439
G1 F2027.944
G1 X120.858 Y123.671 E.1766
; LINE_WIDTH: 0.997364
G1 F1974.717
G1 X121.225 Y123.791 E.05724
; LINE_WIDTH: 1.04521
G1 F1876.225
G1 X121.591 Y123.911 E.06024
G1 X121.599 Y123.887 F30000
; LINE_WIDTH: 0.839149
G1 F2389.459
G1 X119.692 Y123.311 E.24451
G1 X119.694 Y123.305 F30000
; LINE_WIDTH: 0.666233
G1 F3000
G1 X121.601 Y123.879 E.18839
G1 X123.519 Y120.964 F30000
; LINE_WIDTH: 0.666227
G1 F3000
G1 X122.154 Y119.513 E.18839
G1 X122.149 Y119.518 F30000
; LINE_WIDTH: 0.839146
G1 F2389.468
G1 X123.513 Y120.969 E.24451
G1 X123.494 Y120.986 F30000
; LINE_WIDTH: 1.04521
G1 F1876.237
G1 X123.237 Y120.699 E.06024
; LINE_WIDTH: 0.997358
G1 F1974.73
G1 X122.98 Y120.412 E.05723
; LINE_WIDTH: 0.973434
G1 F2027.956
G1 X122.144 Y119.523 E.1766
; WIPE_START
G1 F24000
G1 X122.98 Y120.412 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X126.167 Y117.462 Z3.6 F30000
G1 Z3.2
G1 E3 F1800
; LINE_WIDTH: 0.973436
G1 F2027.95
G1 X126.447 Y118.651 E.1766
; LINE_WIDTH: 0.997362
G1 F1974.722
G1 X126.526 Y119.028 E.05723
; LINE_WIDTH: 1.04521
G1 F1876.227
G1 X126.605 Y119.405 E.06024
G1 X126.629 Y119.399 F30000
; LINE_WIDTH: 0.839146
G1 F2389.469
G1 X126.174 Y117.461 E.24451
G1 X126.181 Y117.459 F30000
; LINE_WIDTH: 0.66622
G1 F3000
G1 X126.637 Y119.398 E.18839
G1 X130.113 Y119.599 F30000
; LINE_WIDTH: 0.820834
G1 F2449.003
G1 X130.689 Y117.692 E.23857
G1 X130.695 Y117.694 F30000
; LINE_WIDTH: 0.666236
G1 F3000
G1 X130.121 Y119.601 E.18839
G1 X130.617 Y119.727 F30000
; LINE_WIDTH: 1.06129
G1 F1845.308
G1 X130.242 Y119.123 E.11294
G1 X130.286 Y118.991 E.02217
; LINE_WIDTH: 0.997363
G1 F1974.718
G1 X130.329 Y118.858 E.02072
; LINE_WIDTH: 0.968185
G1 F2040.02
G1 X130.682 Y117.69 E.17555
; WIPE_START
G1 F24000
G1 X130.329 Y118.858 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X134.477 Y120.144 Z3.6 F30000
G1 Z3.2
G1 E3 F1800
; LINE_WIDTH: 0.968185
G1 F2040.02
G1 X133.588 Y120.98 E.17555
; LINE_WIDTH: 0.99736
G1 F1974.725
G1 X133.484 Y121.073 E.02072
; LINE_WIDTH: 1.06126
G1 F1845.354
G1 X133.38 Y121.166 E.02217
G1 X132.679 Y121.067 E.1126
G1 X133.031 Y121.513 F30000
; LINE_WIDTH: 0.820827
G1 F2449.026
G1 X134.482 Y120.149 E.23856
G1 X134.487 Y120.154 F30000
; LINE_WIDTH: 0.649729
G1 F3000
G1 X133.036 Y121.519 E.18303
; WIPE_START
G1 F24000
G1 X134.487 Y120.154 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X136.541 Y124.181 Z3.6 F30000
G1 Z3.2
G1 E3 F1800
; LINE_WIDTH: 0.978111
G1 F2017.326
G1 X135.871 Y124.33 E.09979
; LINE_WIDTH: 1.01092
G1 F1945.789
G1 X135.201 Y124.479 E.10345
; LINE_WIDTH: 1.06183
G1 F1844.281
G1 X135.076 Y124.503 E.02032
G1 X134.519 Y124.067 E.11252
G1 X132.401 Y123.698 F30000
; LINE_WIDTH: 0.676032
G1 F3000
G1 X132.008 Y122.904 E.08519
; LINE_WIDTH: 0.687638
G1 F2991.039
G1 X131.911 Y122.782 E.01528
; LINE_WIDTH: 0.72289
G1 F2825.529
G1 X131.815 Y122.659 E.01617
G1 X131.218 Y122.159 E.08088
; LINE_WIDTH: 0.678118
G1 F3000
G2 X130.293 Y121.544 I-3.763 J4.658 E.10736
; LINE_WIDTH: 0.695449
G1 F2952.715
G1 X130.067 Y121.427 E.02528
; LINE_WIDTH: 0.725544
G1 F2813.805
G2 X129.809 Y121.294 I-2.587 J4.697 E.03022
; LINE_WIDTH: 0.759486
G1 F2672.029
G2 X129.324 Y121.144 I-.602 J1.088 E.05619
; LINE_WIDTH: 0.694051
G1 F2959.505
G2 X128.557 Y121.027 I-2.682 J14.946 E.07686
; LINE_WIDTH: 0.678495
G1 F3000
G1 X128.251 Y121 E.0297
G2 X127.679 Y120.997 I-.499 J38.245 E.05526
; LINE_WIDTH: 0.702751
G1 F2917.766
G1 X127.425 Y121.01 E.02559
; LINE_WIDTH: 0.737171
G1 F2763.575
G2 X127.135 Y121.026 I.151 J5.378 E.03086
; LINE_WIDTH: 0.75487
G1 F2690.467
G1 X127.017 Y121.039 E.01289
G1 X126.644 Y121.159 E.04277
; LINE_WIDTH: 0.684322
G1 F3000
G2 X125.153 Y121.869 I2.281 J6.705 E.16139
; LINE_WIDTH: 0.7113
G1 F2877.885
G1 X124.941 Y122.009 E.02596
; LINE_WIDTH: 0.750067
G1 F2709.919
G2 X124.698 Y122.171 I2.865 J4.573 E.03158
; LINE_WIDTH: 0.777348
G1 F2603.01
G1 X124.667 Y122.194 E.00434
; LINE_WIDTH: 0.763018
G1 F2658.092
G1 X124.51 Y122.37 E.02602
; LINE_WIDTH: 0.722194
G1 F2828.617
G2 X124.332 Y122.571 I3.652 J3.411 E.02791
; LINE_WIDTH: 0.683276
G1 F3000
G2 X123.432 Y123.916 I5.146 J4.415 E.15786
; LINE_WIDTH: 0.720953
G1 F2834.146
G1 X123.321 Y124.143 E.02618
; LINE_WIDTH: 0.762864
G1 F2658.699
G1 X123.2 Y124.41 E.03235
; LINE_WIDTH: 0.753439
G1 F2696.232
G1 X123.151 Y124.66 E.02772
; LINE_WIDTH: 0.713805
G1 F2866.405
G2 X123.095 Y124.942 I5.215 J1.167 E.02944
; LINE_WIDTH: 0.68364
G1 F3000
G1 X123.023 Y125.445 E.04951
G2 X123.006 Y126.558 I7.376 J.673 E.1085
; LINE_WIDTH: 0.72856
G1 F2800.599
G1 X123.022 Y126.77 E.02235
; LINE_WIDTH: 0.766986
G1 F2642.61
G2 X123.072 Y127.098 I.902 J.029 E.03704
; LINE_WIDTH: 0.740478
G1 F2749.615
G1 X123.156 Y127.339 E.02716
; LINE_WIDTH: 0.691934
G1 F2969.842
G2 X123.413 Y128.004 I6.608 J-2.17 E.07051
; LINE_WIDTH: 0.685448
G1 F3000
G1 X123.446 Y128.079 E.00797
G2 X123.997 Y129.046 I7.29 J-3.514 E.10888
; LINE_WIDTH: 0.73681
G1 F2765.108
G1 X124.096 Y129.189 E.01843
; LINE_WIDTH: 0.766506
G1 F2644.473
G2 X124.34 Y129.468 I1.055 J-.678 E.04127
; LINE_WIDTH: 0.728792
G1 F2799.59
G1 X124.534 Y129.633 E.02667
; LINE_WIDTH: 0.682253
G1 F3000
G2 X125.647 Y130.422 I4.06 J-4.544 E.13286
; LINE_WIDTH: 0.702298
G1 F2919.911
G1 X126.096 Y130.66 E.05111
; LINE_WIDTH: 0.729424
G1 F2796.842
G1 X126.128 Y130.675 E.00365
; LINE_WIDTH: 0.745695
G1 F2727.877
G1 X126.249 Y130.731 E.01441
; LINE_WIDTH: 0.765598
G1 F2648.003
G2 X126.608 Y130.842 I.444 J-.803 E.04184
; LINE_WIDTH: 0.733669
G1 F2778.514
G1 X126.642 Y130.849 E.0037
; LINE_WIDTH: 0.718315
G1 F2845.967
G1 X126.892 Y130.893 E.02622
; LINE_WIDTH: 0.680893
G1 F3000
G2 X128.252 Y131.005 I1.168 J-5.861 E.13254
; LINE_WIDTH: 0.696248
G1 F2948.849
G1 X128.506 Y130.993 E.02531
; LINE_WIDTH: 0.726858
G1 F2808.038
G2 X128.795 Y130.979 I-.114 J-5.36 E.03029
; LINE_WIDTH: 0.759136
G1 F2673.42
G2 X129.29 Y130.864 I-.029 J-1.243 E.05616
; LINE_WIDTH: 0.693589
G1 F2961.753
G2 X130.004 Y130.586 I-5.227 J-14.45 E.07586
; LINE_WIDTH: 0.67865
G1 F3000
G2 X130.788 Y130.168 I-2.529 J-5.683 E.0859
; LINE_WIDTH: 0.703701
G1 F2913.278
G1 X131.001 Y130.029 E.02563
; LINE_WIDTH: 0.738637
G1 F2757.367
G2 X131.244 Y129.869 I-2.823 J-4.577 E.03094
; LINE_WIDTH: 0.771822
G1 F2623.979
G1 X131.332 Y129.805 E.01216
; LINE_WIDTH: 0.763023
G1 F2658.074
G1 X131.497 Y129.623 E.02708
; LINE_WIDTH: 0.71985
G1 F2839.073
G1 X131.661 Y129.441 E.02536
; LINE_WIDTH: 0.676678
G1 F3000
G1 X131.826 Y129.259 E.02363
; LINE_WIDTH: 0.624944
G2 X132.055 Y128.988 I-1.174 J-1.226 E.0312
G1 X132.301 Y128.403 E.05581
G1 X134.399 Y128.121 F30000
; LINE_WIDTH: 0.649726
G1 F3000
G1 X136.306 Y128.695 E.18303
G1 X136.308 Y128.689 F30000
; LINE_WIDTH: 0.820833
G1 F2449.007
G1 X134.401 Y128.113 E.23857
G1 X134.612 Y127.585 F30000
; LINE_WIDTH: 1.06127
G1 F1845.341
G1 X134.877 Y128.242 E.11259
G1 X135.009 Y128.286 E.02217
; LINE_WIDTH: 0.99737
G1 F1974.703
G1 X135.142 Y128.329 E.02072
; LINE_WIDTH: 0.96819
G1 F2040.009
G1 X136.31 Y128.682 E.17556
; WIPE_START
G1 F24000
G1 X135.142 Y128.329 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X133.856 Y132.477 Z3.6 F30000
G1 Z3.2
G1 E3 F1800
; LINE_WIDTH: 0.968175
G1 F2040.043
G1 X133.02 Y131.588 E.17555
; LINE_WIDTH: 0.997358
G1 F1974.729
G1 X132.927 Y131.484 E.02072
; LINE_WIDTH: 1.06126
G1 F1845.356
G1 X132.834 Y131.38 E.02217
G1 X132.933 Y130.679 E.11261
G1 X132.487 Y131.031 F30000
; LINE_WIDTH: 0.820846
G1 F2448.961
G1 X133.851 Y132.482 E.23857
G1 X133.846 Y132.487 F30000
; LINE_WIDTH: 0.649723
G1 F3000
G1 X132.481 Y131.036 E.18303
G1 X129.933 Y132.519 F30000
; LINE_WIDTH: 1.06183
G1 F1844.279
G1 X129.497 Y133.076 E.11252
G1 X129.521 Y133.201 E.02032
; LINE_WIDTH: 1.01092
G1 F1945.788
G1 X129.67 Y133.871 E.10346
; LINE_WIDTH: 0.978111
G1 F2017.326
G1 X129.819 Y134.541 E.09979
; WIPE_START
G1 F24000
G1 X129.67 Y133.871 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X125.318 Y134.31 Z3.6 F30000
G1 Z3.2
G1 E3 F1800
; LINE_WIDTH: 0.973446
G1 F2027.928
G1 X125.671 Y133.142 E.1766
; LINE_WIDTH: 0.997369
G1 F1974.706
G1 X125.791 Y132.775 E.05723
; LINE_WIDTH: 1.04522
G1 F1876.218
G1 X125.911 Y132.409 E.06024
G1 X125.887 Y132.401 F30000
; LINE_WIDTH: 0.839148
G1 F2389.463
G1 X125.311 Y134.308 E.24451
G1 X125.305 Y134.306 F30000
; LINE_WIDTH: 0.666241
G1 F3000
G1 X125.879 Y132.399 E.1884
G1 X122.964 Y130.481 F30000
; LINE_WIDTH: 0.666228
G1 F3000
G1 X121.513 Y131.846 E.18839
G1 X121.518 Y131.851 F30000
; LINE_WIDTH: 0.839146
G1 F2389.469
G1 X122.969 Y130.487 E.24451
G1 X122.986 Y130.506 F30000
; LINE_WIDTH: 1.04521
G1 F1876.235
G1 X122.699 Y130.763 E.06024
; LINE_WIDTH: 0.997359
G1 F1974.728
G1 X122.412 Y131.02 E.05723
; LINE_WIDTH: 0.973432
G1 F2027.96
G1 X121.523 Y131.856 E.17659
; WIPE_START
G1 F24000
G1 X122.412 Y131.02 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X129.265 Y127.66 Z3.6 F30000
G1 X132.182 Y126.231 Z3.6
G1 Z3.2
G1 E3 F1800
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.811188
G1 F2481.569
G1 X132.166 Y126.789 E.06604
; LINE_WIDTH: 0.769598
G1 F2632.514
G2 X132.151 Y127.573 I14.165 J.671 E.08738
G1 X132.696 Y127.803 E.06598
G2 X132.828 Y127.385 I-.493 J-.384 E.04985
; LINE_WIDTH: 0.780303
G1 F2591.933
G1 X132.874 Y126.828 E.06322
; LINE_WIDTH: 0.828061
G1 F2425.158
G2 X132.922 Y126.236 I-14.7 J-1.501 E.07185
G1 X132.935 Y125.098 E.13766
G1 X132.904 Y124.942 E.01926
G1 X132.664 Y124.395 E.07226
G1 X132.186 Y124.632 E.06452
G3 X132.182 Y126.111 I-196.829 J.23 E.1789
; CHANGE_LAYER
; Z_HEIGHT: 3.6
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X132.186 Y124.632 E-2.1075
G1 X132.653 Y124.401 E-.7425
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 9/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L9
M991 S0 P8 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z3.6 I.829 J-.891 P1  F30000
G1 X131.343 Y123.182 Z3.6
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2451.784
G1 X131.444 Y123.276 E.01646
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X128.96 Y130.232 I-2.818 J-3.446 E.24465
G1 X128.96 Y130.232 E0
G3 X127.908 Y121.661 I-.966 J-4.232 E1.73767
G3 X130.78 Y122.66 I.083 J4.39 E.37154
G1 X131.255 Y123.101 E.07757
G1 X130.71 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X127.913 Y122.395 I-2.307 J-2.774 E1.64473
G1 X128.17 Y122.393 E.03071
G3 X130.627 Y123.509 I-.217 J3.743 E.33037
M204 S10000
; WIPE_START
M73 P70 R3
G1 F24000
G1 X130.661 Y125.509 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.261 Y127.379 Z4 F30000
G1 X122.375 Y127.603 Z4
G1 Z3.6
G1 E3 F1800
; FEATURE: Inner wall
G1 F2451.784
G1 X121.859 Y127.688 E.06251
G1 X121.763 Y127.29 E.04901
G1 X122.357 Y127.1 E.07461
G3 X122.425 Y124.613 I14.266 J-.855 E.29814
G1 X121.838 Y124.392 E.0751
G1 X121.954 Y123.999 E.04901
G1 X122.563 Y124.132 E.0746
G3 X123.866 Y122.011 I12.783 J6.394 E.29814
G1 X123.502 Y121.567 E.06869
G1 X123.803 Y121.285 E.0494
G1 X124.214 Y121.671 E.06737
G3 X126.414 Y120.478 I7.915 J11.98 E.29985
G1 X126.312 Y119.859 E.07511
G1 X126.71 Y119.763 E.04901
G1 X126.9 Y120.357 E.07461
G3 X129.387 Y120.425 I.855 J14.266 E.29814
G1 X129.608 Y119.838 E.0751
G1 X130.001 Y119.954 E.04901
G1 X129.868 Y120.563 E.0746
G3 X131.989 Y121.866 I-6.394 J12.783 E.29814
G1 X132.474 Y121.468 E.07511
G1 X132.756 Y121.765 E.04901
G1 X132.337 Y122.226 E.07461
G3 X133.522 Y124.414 I-11.927 J7.873 E.29814
G1 X134.141 Y124.312 E.0751
G1 X134.237 Y124.71 E.04901
G1 X133.643 Y124.9 E.07461
G3 X133.575 Y127.387 I-14.266 J.855 E.29814
G1 X134.112 Y127.59 E.06869
G1 X133.992 Y127.985 E.0494
G1 X133.444 Y127.856 E.06736
G3 X132.134 Y129.989 I-12.846 J-6.419 E.29985
G1 X132.532 Y130.474 E.07511
G1 X132.235 Y130.756 E.04901
G1 X131.774 Y130.337 E.07461
G3 X129.586 Y131.522 I-7.873 J-11.927 E.29814
G1 X129.688 Y132.141 E.0751
G1 X129.29 Y132.237 E.04901
G1 X129.1 Y131.643 E.07461
G3 X126.613 Y131.575 I-.855 J-14.266 E.29814
G1 X126.41 Y132.112 E.06869
G1 X126.015 Y131.992 E.0494
G1 X126.144 Y131.444 E.06736
G3 X124.011 Y130.134 I6.419 J-12.846 E.29985
G1 X123.567 Y130.498 E.06869
G1 X123.285 Y130.197 E.0494
G1 X123.671 Y129.786 E.06737
G3 X122.484 Y127.599 I11.98 J-7.915 E.29809
G1 X122.053 Y128.4 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X121.98 Y128.412 E.00877
G3 X119.241 Y128.469 I-1.526 J-7.492 E.32959
G1 X119.199 Y128.311 E.01961
G3 X119.076 Y127.788 I5.926 J-1.665 E.06427
G3 X121.61 Y126.568 I4.54 J6.189 E.33839
G3 X121.649 Y125.105 I10.142 J-.461 E.17527
G1 X121.581 Y125.079 E.00877
G3 X119.18 Y123.759 I2.424 J-7.251 E.32959
G1 X119.223 Y123.601 E.01961
G3 X119.378 Y123.087 I5.964 J1.521 E.06427
G3 X122.182 Y123.297 I.837 J7.63 E.33839
G3 X122.948 Y122.05 I9.015 J4.672 E.17527
G1 X122.901 Y121.993 E.00877
G3 X121.482 Y119.649 I5.725 J-5.067 E.32959
G1 X121.598 Y119.533 E.01961
G3 X121.99 Y119.166 I4.405 J4.3 E.06427
G3 X124.309 Y120.753 I-2.843 J6.642 E.33839
G3 X125.6 Y120.053 I5.484 J8.569 E.17588
G1 X125.588 Y119.98 E.00877
G3 X125.531 Y117.241 I7.492 J-1.526 E.32959
G1 X125.689 Y117.199 E.01961
G3 X126.213 Y117.076 I1.668 J5.938 E.06439
G3 X127.432 Y119.61 I-6.222 J4.553 E.33835
G3 X128.895 Y119.649 I.461 J10.142 E.17527
G1 X128.921 Y119.581 E.00877
G3 X130.241 Y117.18 I7.251 J2.424 E.32959
G1 X130.399 Y117.223 E.01961
G3 X130.913 Y117.378 I-1.521 J5.965 E.06427
G3 X130.703 Y120.182 I-7.63 J.837 E.33839
G3 X131.95 Y120.948 I-4.672 J9.015 E.17527
G1 X132.007 Y120.901 E.00877
G3 X134.351 Y119.482 I5.067 J5.725 E.32959
G1 X134.467 Y119.598 E.01961
G3 X134.834 Y119.99 I-4.3 J4.405 E.06427
G3 X133.25 Y122.313 I-7.026 J-3.09 E.33839
G3 X133.947 Y123.6 I-8.553 J5.471 E.17527
G1 X134.02 Y123.588 E.00877
G3 X136.759 Y123.531 I1.526 J7.491 E.32959
G1 X136.801 Y123.689 E.01961
G3 X136.924 Y124.212 I-5.926 J1.665 E.06427
G3 X134.39 Y125.432 I-4.54 J-6.189 E.33839
G3 X134.351 Y126.895 I-10.142 J.461 E.17527
G1 X134.419 Y126.921 E.00877
G3 X136.82 Y128.241 I-2.424 J7.251 E.32959
G1 X136.777 Y128.399 E.01961
G3 X136.622 Y128.913 I-5.964 J-1.521 E.06427
G3 X133.82 Y128.698 I-.859 J-7.174 E.33839
G3 X133.052 Y129.95 I-9.035 J-4.68 E.17588
G1 X133.099 Y130.007 E.00877
G3 X134.518 Y132.351 I-5.725 J5.067 E.32959
G1 X134.402 Y132.467 E.01961
G3 X134.01 Y132.834 I-4.405 J-4.3 E.06427
G3 X131.687 Y131.25 I3.09 J-7.026 E.33839
G3 X130.4 Y131.947 I-5.471 J-8.553 E.17527
G1 X130.412 Y132.02 E.00877
G3 X130.469 Y134.759 I-7.491 J1.526 E.32959
G1 X130.311 Y134.801 E.01961
G3 X129.788 Y134.924 I-1.665 J-5.927 E.06427
G3 X128.568 Y132.39 I6.189 J-4.54 E.33839
G3 X127.105 Y132.351 I-.461 J-10.142 E.17527
G1 X127.079 Y132.419 E.00877
G3 X125.759 Y134.82 I-7.251 J-2.424 E.32959
G1 X125.601 Y134.777 E.01961
G3 X125.087 Y134.622 I1.521 J-5.965 E.06427
G3 X125.302 Y131.82 I7.174 J-.859 E.33839
G3 X124.05 Y131.052 I4.68 J-9.035 E.17588
G1 X123.993 Y131.099 E.00877
G3 X121.649 Y132.518 I-5.067 J-5.725 E.32959
G1 X121.533 Y132.402 E.01961
G3 X121.166 Y132.01 I4.3 J-4.405 E.06427
G3 X122.753 Y129.691 I6.642 J2.843 E.33839
G3 X122.103 Y128.509 I8.569 J-5.484 E.16152
M204 S10000
; WIPE_START
G1 F24000
G1 X121.98 Y128.412 E-.22266
G1 X121.394 Y128.509 E-.84701
G1 X120.699 Y128.57 E-.99369
G1 X120.147 Y128.563 E-.78665
; WIPE_END
G1 E-.15 F1800
G1 X121.449 Y127.551 Z4 F30000
G1 Z3.6
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 0.839477
G1 F2388.421
G1 X119.515 Y128.062 E.24566
G1 X119.513 Y128.055 F30000
; LINE_WIDTH: 0.666543
G1 F3000
G1 X121.447 Y127.544 E.18929
G1 X120.973 Y127.691 F30000
; LINE_WIDTH: 1.05927
G1 F1849.131
G1 X121.293 Y127.055 E.11307
G1 X120.973 Y127.691 F30000
; LINE_WIDTH: 1.04709
G1 F1872.561
G1 X120.834 Y127.724 E.02231
; LINE_WIDTH: 0.998227
G1 F1972.85
G1 X120.695 Y127.757 E.02118
; LINE_WIDTH: 0.973795
G1 F2027.132
G1 X119.517 Y128.069 E.17649
G1 X123.077 Y127.173 F30000
; LINE_WIDTH: 0.76861
G1 F2636.323
G1 X123.153 Y127.377 E.02428
; LINE_WIDTH: 0.727865
G1 F2803.63
G2 X123.242 Y127.613 I4.423 J-1.531 E.02636
; LINE_WIDTH: 0.684237
G1 F3000
G2 X124.005 Y129.04 I6.377 J-2.493 E.15813
; LINE_WIDTH: 0.719215
G1 F2841.923
G1 X124.154 Y129.246 E.0263
; LINE_WIDTH: 0.761339
G1 F2664.7
G2 X124.327 Y129.482 I1.449 J-.88 E.03222
; LINE_WIDTH: 0.763061
G1 F2657.926
G1 X124.524 Y129.643 E.02813
; LINE_WIDTH: 0.720205
G1 F2837.487
G2 X124.748 Y129.824 I3.47 J-4.065 E.02978
; LINE_WIDTH: 0.684275
G1 F3000
G2 X126.131 Y130.664 I4.293 J-5.511 E.15817
; LINE_WIDTH: 0.727968
G1 F2803.185
G1 X126.343 Y130.757 E.02418
; LINE_WIDTH: 0.769584
G1 F2632.568
G2 X126.638 Y130.867 I.409 J-.649 E.03532
; LINE_WIDTH: 0.749152
G1 F2713.657
G1 X126.89 Y130.905 E.02753
; LINE_WIDTH: 0.710592
G1 F2881.145
G2 X127.174 Y130.947 I.93 J-5.255 E.02927
; LINE_WIDTH: 0.685154
G1 F3000
G1 X127.711 Y130.999 E.05273
G2 X128.793 Y130.966 I.291 J-8.396 E.10573
; LINE_WIDTH: 0.736135
G1 F2767.978
G1 X128.983 Y130.944 E.02028
; LINE_WIDTH: 0.770897
G1 F2627.521
G2 X129.328 Y130.869 I-.052 J-1.06 E.03965
; LINE_WIDTH: 0.73651
G1 F2766.383
G1 X129.564 Y130.774 E.027
; LINE_WIDTH: 0.683824
G1 F3000
M73 P71 R3
G2 X130.785 Y130.163 I-2.121 J-5.764 E.13324
; LINE_WIDTH: 0.701034
G1 F2925.911
G1 X131.206 Y129.879 E.051
; LINE_WIDTH: 0.727205
G1 F2806.518
G1 X131.234 Y129.859 E.00362
; LINE_WIDTH: 0.744952
G1 F2730.951
G1 X131.355 Y129.767 E.01629
; LINE_WIDTH: 0.775357
G1 F2610.528
G1 X131.476 Y129.676 E.01705
; LINE_WIDTH: 0.768986
G1 F2634.871
G1 X131.605 Y129.527 E.02195
; LINE_WIDTH: 0.725842
G1 F2812.495
G1 X131.734 Y129.377 E.02057
; LINE_WIDTH: 0.682698
G1 F3000
G1 X131.863 Y129.228 E.01918
; LINE_WIDTH: 0.626519
G1 X131.992 Y129.079 E.01737
G1 X132.377 Y128.379 E.0704
G1 X132.258 Y128.349 F30000
; LINE_WIDTH: 0.784179
G1 F2577.548
G1 X131.849 Y129.755 E.16672
G1 X132.619 Y130.898 F30000
; LINE_WIDTH: 0.821174
G1 F2447.87
G1 X134.028 Y132.317 E.23969
G1 X134.023 Y132.322 F30000
; LINE_WIDTH: 0.650025
G1 F3000
G1 X132.613 Y130.903 E.1839
G1 X132.267 Y131.281 F30000
; LINE_WIDTH: 1.06397
G1 F1840.242
G1 X132.977 Y131.239 E.11337
G1 X133.076 Y131.344 E.02308
; LINE_WIDTH: 0.998227
G1 F1972.848
G1 X133.174 Y131.447 E.02118
; LINE_WIDTH: 0.96854
G1 F2039.199
G1 X134.034 Y132.312 E.17544
; WIPE_START
G1 F24000
G1 X133.174 Y131.447 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X135.205 Y128.13 Z4 F30000
G1 Z3.6
G1 E3 F1800
; LINE_WIDTH: 0.968545
G1 F2039.188
G1 X136.382 Y128.45 E.17544
G1 X136.379 Y128.457 F30000
; LINE_WIDTH: 0.821174
G1 F2447.871
G1 X134.396 Y127.918 E.24633
G1 X134.403 Y127.893 F30000
; LINE_WIDTH: 1.07652
G1 F1816.934
G2 X134.932 Y128.049 I3.453 J-10.695 E.08893
; LINE_WIDTH: 1.04709
G1 F1872.558
G1 X135.068 Y128.09 E.02231
; LINE_WIDTH: 0.998229
G1 F1972.845
G1 X135.205 Y128.13 E.02118
; WIPE_START
G1 F24000
G1 X135.068 Y128.09 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X134.707 Y124.945 Z4 F30000
G1 Z3.6
G1 E3 F1800
; LINE_WIDTH: 1.06398
G1 F1840.231
G1 X135.025 Y124.309 E.11336
G1 X135.166 Y124.276 E.02308
; LINE_WIDTH: 0.998229
G1 F1972.844
G1 X135.304 Y124.243 E.02118
; LINE_WIDTH: 0.968549
G1 F2039.18
G1 X136.483 Y123.931 E.17544
G1 X136.485 Y123.938 F30000
; LINE_WIDTH: 0.821154
G1 F2447.936
G1 X134.551 Y124.449 E.23969
G1 X134.553 Y124.456 F30000
; LINE_WIDTH: 0.650018
G1 F3000
G1 X136.487 Y123.945 E.1839
; WIPE_START
G1 F24000
G1 X134.553 Y124.456 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X133.281 Y121.733 Z4 F30000
G1 Z3.6
G1 E3 F1800
; LINE_WIDTH: 1.06397
G1 F1840.242
G1 X133.239 Y121.023 E.11336
G1 X133.344 Y120.924 E.02308
; LINE_WIDTH: 0.998226
G1 F1972.85
G1 X133.447 Y120.826 E.02117
; LINE_WIDTH: 0.968539
G1 F2039.202
G1 X134.314 Y119.965 E.17573
G1 X134.319 Y119.97 F30000
; LINE_WIDTH: 0.821174
G1 F2447.87
G1 X132.898 Y121.381 E.23994
G1 X132.903 Y121.387 F30000
; LINE_WIDTH: 0.650008
G1 F3000
G1 X134.323 Y119.975 E.18408
G1 X131.786 Y122.651 F30000
; LINE_WIDTH: 0.710594
G1 F2881.138
G1 X131.893 Y122.782 E.01719
; LINE_WIDTH: 0.664232
G1 F3000
G1 X132 Y122.912 E.01592
; LINE_WIDTH: 0.657279
G1 X132.393 Y123.674 E.07981
G1 X131.786 Y122.651 F30000
; LINE_WIDTH: 0.742118
G1 F2742.744
G1 X131.68 Y122.52 E.01806
G1 X131.223 Y122.154 E.06263
; LINE_WIDTH: 0.685186
G1 F3000
G2 X129.805 Y121.307 I-4.329 J5.633 E.16166
; LINE_WIDTH: 0.735139
G1 F2772.224
G1 X129.625 Y121.229 E.02075
; LINE_WIDTH: 0.770974
G1 F2627.227
G2 X129.293 Y121.121 I-.476 J.903 E.03914
; LINE_WIDTH: 0.737947
G1 F2760.287
G1 X129.042 Y121.085 E.02706
; LINE_WIDTH: 0.684079
G1 F3000
G2 X127.68 Y121.002 I-1.054 J6.069 E.1333
; LINE_WIDTH: 0.700173
G1 F2930.01
G1 X127.172 Y121.037 E.05093
; LINE_WIDTH: 0.725831
G1 F2812.544
G1 X127.138 Y121.04 E.00361
; LINE_WIDTH: 0.743867
G1 F2735.454
G1 X126.983 Y121.059 E.01677
; LINE_WIDTH: 0.76887
G1 F2635.319
G2 X126.607 Y121.156 I.165 J1.423 E.04331
; LINE_WIDTH: 0.726398
G1 F2810.053
G1 X126.371 Y121.252 E.02657
; LINE_WIDTH: 0.682265
G1 F3000
G2 X125.157 Y121.874 I2.115 J5.624 E.13288
; LINE_WIDTH: 0.694387
G1 F2957.867
G1 X124.947 Y122.018 E.02523
; LINE_WIDTH: 0.72353
G1 F2822.691
G2 X124.709 Y122.182 I2.925 J4.495 E.03011
; LINE_WIDTH: 0.763859
G1 F2654.797
G2 X124.344 Y122.536 I.646 J1.033 E.05656
; LINE_WIDTH: 0.731159
M73 P71 R2
G1 F2789.322
G1 X124.322 Y122.563 E.00367
; LINE_WIDTH: 0.703706
G1 F2913.258
G1 X124.013 Y122.967 E.05123
; LINE_WIDTH: 0.67892
G1 F3000
G2 X123.44 Y123.918 I4.806 J3.545 E.10753
; LINE_WIDTH: 0.701415
G1 F2924.098
G1 X123.331 Y124.149 E.02554
; LINE_WIDTH: 0.734882
G1 F2773.323
G2 X123.209 Y124.412 I4.811 J2.398 E.03074
; LINE_WIDTH: 0.760815
G1 F2666.769
G1 X123.151 Y124.555 E.0169
G1 X123.089 Y124.906 E.03928
; LINE_WIDTH: 0.685765
G1 F3000
G2 X123.015 Y126.556 I6.97 J1.141 E.16184
; LINE_WIDTH: 0.709682
G1 F2885.349
G1 X123.038 Y126.81 E.02589
; LINE_WIDTH: 0.747487
G1 F2720.488
G2 X123.066 Y127.1 I5.376 J-.372 E.03144
; LINE_WIDTH: 0.778517
G1 F2598.618
G1 X123.077 Y127.173 E.00834
G1 X123.141 Y130.58 F30000
; LINE_WIDTH: 0.83949
G1 F2388.378
G1 X121.683 Y132.028 E.25246
G1 X121.688 Y132.034 F30000
; LINE_WIDTH: 0.973796
G1 F2027.13
G1 X122.553 Y131.174 E.17649
; LINE_WIDTH: 0.998227
G1 F1972.849
G1 X122.656 Y131.076 E.02118
; LINE_WIDTH: 1.04709
G1 F1872.564
G1 X122.76 Y130.978 E.02231
; LINE_WIDTH: 1.08057
G1 F1809.53
G3 X123.159 Y130.599 I7.928 J7.951 E.08928
G1 X126.082 Y132.396 F30000
; LINE_WIDTH: 0.839489
G1 F2388.381
G1 X125.543 Y134.379 E.25247
G1 X125.55 Y134.382 F30000
; LINE_WIDTH: 0.973796
G1 F2027.13
G1 X125.87 Y133.205 E.17649
; LINE_WIDTH: 0.998227
G1 F1972.849
G1 X125.91 Y133.068 E.02118
; LINE_WIDTH: 1.04709
G1 F1872.559
G1 X125.951 Y132.932 E.02231
; LINE_WIDTH: 1.08058
G1 F1809.514
G3 X126.107 Y132.403 I10.852 J2.925 E.08929
G1 X129.055 Y132.707 F30000
; LINE_WIDTH: 1.06398
G1 F1840.234
G1 X129.691 Y133.025 E.11336
G1 X129.724 Y133.166 E.02308
; LINE_WIDTH: 0.998226
G1 F1972.851
G1 X129.757 Y133.305 E.02118
; LINE_WIDTH: 0.968547
G1 F2039.183
G1 X130.069 Y134.483 E.17544
G1 X130.062 Y134.485 F30000
; LINE_WIDTH: 0.821155
G1 F2447.934
G1 X129.551 Y132.551 E.23969
G1 X129.544 Y132.553 F30000
; LINE_WIDTH: 0.666536
G1 F3000
G1 X130.055 Y134.487 E.18929
G1 X132.183 Y126.116 F30000
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.81182
G1 F2479.409
G2 X132.162 Y127.441 I36.034 J1.221 E.15682
G2 X132.694 Y127.727 I7.427 J-13.144 E.07146
G1 X132.855 Y127.386 E.04466
G2 X132.91 Y124.91 I-17.56 J-1.628 E.29325
G2 X132.677 Y124.352 I-2.196 J.587 E.07169
G1 X132.177 Y124.61 E.06657
G2 X132.182 Y125.996 I147.588 J.154 E.16393
G1 X130.44 Y119.664 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 1.06398
G1 F1840.221
G1 X130.048 Y119.071 E.11336
G1 X130.09 Y118.932 E.02309
; LINE_WIDTH: 0.998229
G1 F1972.845
G1 X130.13 Y118.795 E.02118
; LINE_WIDTH: 0.968543
G1 F2039.193
G1 X130.45 Y117.616 E.17573
G1 X130.457 Y117.619 F30000
; LINE_WIDTH: 0.821162
G1 F2447.908
G1 X129.932 Y119.551 E.23994
G1 X129.94 Y119.553 F30000
; LINE_WIDTH: 0.666533
G1 F3000
G1 X130.464 Y117.621 E.18948
; WIPE_START
G1 F24000
G1 X129.94 Y119.551 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X126.945 Y119.293 Z4 F30000
G1 Z3.6
G1 E3 F1800
; LINE_WIDTH: 1.05929
G1 F1849.094
G1 X126.309 Y118.973 E.11308
; LINE_WIDTH: 1.04709
G1 F1872.567
G1 X126.276 Y118.834 E.02231
; LINE_WIDTH: 0.998222
G1 F1972.859
G1 X126.243 Y118.695 E.02118
; LINE_WIDTH: 0.97379
G1 F2027.142
G1 X125.931 Y117.517 E.17648
G1 X125.938 Y117.515 F30000
; LINE_WIDTH: 0.839486
G1 F2388.391
G1 X126.449 Y119.449 E.24566
G1 X126.456 Y119.447 F30000
; LINE_WIDTH: 0.666532
G1 F3000
G1 X125.945 Y117.513 E.18929
; WIPE_START
G1 F24000
G1 X126.456 Y119.447 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X122.826 Y120.553 Z4 F30000
G1 Z3.6
G1 E3 F1800
; LINE_WIDTH: 0.998226
G1 F1972.85
G1 X122.924 Y120.656 E.02117
; LINE_WIDTH: 1.04709
G1 F1872.567
G1 X123.022 Y120.76 E.02231
; LINE_WIDTH: 1.08057
G1 F1809.532
G3 X123.401 Y121.159 I-7.966 J7.942 E.08929
G1 X123.42 Y121.141 F30000
; LINE_WIDTH: 0.83949
G1 F2388.379
G1 X121.972 Y119.683 E.25246
G1 X121.966 Y119.688 F30000
; LINE_WIDTH: 0.973794
G1 F2027.134
G1 X122.826 Y120.553 E.17649
; WIPE_START
G1 F24000
G1 X121.966 Y119.688 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X121.664 Y123.56 Z4 F30000
G1 Z3.6
G1 E3 F1800
; LINE_WIDTH: 1.05929
G1 F1849.093
G1 X121.068 Y123.951 E.11307
; LINE_WIDTH: 1.04709
G1 F1872.558
G1 X120.932 Y123.91 E.02231
; LINE_WIDTH: 0.998229
G1 F1972.845
G1 X120.795 Y123.87 E.02118
; LINE_WIDTH: 0.973796
G1 F2027.128
G1 X119.618 Y123.55 E.17649
G1 X119.621 Y123.543 F30000
; LINE_WIDTH: 0.839491
G1 F2388.376
G1 X121.551 Y124.068 E.24567
G1 X121.553 Y124.06 F30000
; LINE_WIDTH: 0.666532
G1 F3000
G1 X119.623 Y123.537 E.18929
; CHANGE_LAYER
; Z_HEIGHT: 4
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X121.553 Y124.06 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 10/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L10
M991 S0 P9 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z4 I.109 J1.212 P1  F30000
G1 X131.343 Y123.183 Z4
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2451.784
G1 X131.444 Y123.276 E.01643
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X127.88 Y121.661 I-2.779 J-3.338 E1.97874
G3 X130.78 Y122.66 I.109 J4.393 E.37484
G1 X131.256 Y123.101 E.07759
G1 X130.71 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X127.885 Y122.395 I-2.309 J-2.773 E1.64221
G1 X128.17 Y122.393 E.03402
G3 X130.627 Y123.509 I-.217 J3.743 E.33037
M204 S10000
; WIPE_START
G1 F24000
G1 X130.661 Y125.509 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.298 Y127.52 Z4.4 F30000
G1 X122.412 Y127.762 Z4.4
G1 Z4
G1 E3 F1800
; FEATURE: Inner wall
G1 F2451.784
G1 X121.897 Y127.861 E.06273
G1 X121.79 Y127.466 E.04894
G1 X122.382 Y127.258 E.07507
G3 X122.377 Y124.765 I17.886 J-1.283 E.29849
G1 X121.784 Y124.56 E.07504
G1 X121.889 Y124.165 E.04894
G1 X122.506 Y124.28 E.07507
G3 X123.747 Y122.119 I16.134 J7.833 E.29849
G1 X123.337 Y121.645 E.07503
G1 X123.625 Y121.355 E.04894
G1 X124.102 Y121.763 E.07506
G3 X126.258 Y120.513 I10.055 J14.85 E.29849
G1 X126.139 Y119.897 E.07504
G1 X126.534 Y119.79 E.04894
G1 X126.742 Y120.382 E.07507
G3 X129.235 Y120.377 I1.283 J17.887 E.29849
G1 X129.44 Y119.784 E.07504
G1 X129.835 Y119.889 E.04894
G1 X129.72 Y120.506 E.07507
G3 X131.881 Y121.747 I-7.834 J16.136 E.29849
G1 X132.355 Y121.337 E.07503
G1 X132.645 Y121.625 E.04894
G1 X132.237 Y122.102 E.07506
G3 X133.487 Y124.258 I-14.849 J10.055 E.29849
G1 X134.103 Y124.139 E.07504
G1 X134.21 Y124.534 E.04894
G1 X133.618 Y124.742 E.07507
G3 X133.623 Y127.235 I-17.887 J1.283 E.29849
G1 X134.216 Y127.44 E.07504
G1 X134.111 Y127.835 E.04894
G1 X133.494 Y127.72 E.07507
G3 X132.253 Y129.881 I-16.137 J-7.835 E.29849
G1 X132.663 Y130.355 E.07503
G1 X132.375 Y130.645 E.04894
G1 X131.898 Y130.237 E.07506
G3 X129.742 Y131.487 I-10.055 J-14.849 E.29849
G1 X129.861 Y132.103 E.07503
G1 X129.466 Y132.21 E.04894
G1 X129.258 Y131.618 E.07507
G3 X126.765 Y131.623 I-1.283 J-17.887 E.29849
G1 X126.56 Y132.216 E.07504
G1 X126.165 Y132.111 E.04894
G1 X126.28 Y131.494 E.07507
G3 X124.119 Y130.253 I7.833 J-16.134 E.29849
G1 X123.645 Y130.663 E.07503
G1 X123.355 Y130.375 E.04894
G1 X123.763 Y129.898 E.07506
G3 X122.52 Y127.758 I14.85 J-10.055 E.29644
G1 X122.117 Y128.566 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X122.048 Y128.579 E.00836
M73 P72 R2
G3 X119.314 Y128.71 I-1.725 J-7.42 E.32926
G1 X119.265 Y128.555 E.0194
G3 X119.131 Y128.034 I12.231 J-3.436 E.06442
G3 X121.625 Y126.746 I4.727 J6.092 E.33778
G3 X121.622 Y125.281 I12.522 J-.759 E.1754
G1 X121.556 Y125.258 E.00836
G3 X119.122 Y124.004 I1.988 J-6.844 E.3296
G1 X119.158 Y123.846 E.01937
G3 X119.302 Y123.327 I12.599 J3.223 E.06441
G3 X122.106 Y123.458 I1.048 J7.639 E.33778
G3 X122.836 Y122.188 I11.225 J5.605 E.1754
G1 X122.79 Y122.135 E.00836
G3 X121.31 Y119.833 I5.563 J-5.203 E.32926
G1 X121.42 Y119.713 E.0194
G3 X121.804 Y119.336 I9.092 J8.875 E.06441
G3 X124.167 Y120.852 I-2.912 J7.139 E.33778
G3 X125.434 Y120.117 I6.919 J10.466 E.1754
G1 X125.421 Y120.048 E.00836
G3 X125.29 Y117.314 I7.42 J-1.725 E.32926
G1 X125.445 Y117.265 E.0194
G3 X125.966 Y117.131 I3.436 J12.229 E.06442
G3 X127.254 Y119.625 I-6.092 J4.727 E.33778
G3 X128.719 Y119.622 I.759 J12.522 E.1754
G1 X128.742 Y119.556 E.00836
G3 X129.996 Y117.123 I6.919 J2.026 E.32953
G1 X130.154 Y117.158 E.01938
G3 X130.673 Y117.302 I-3.202 J12.527 E.06441
G3 X130.542 Y120.106 I-7.639 J1.048 E.33778
G3 X131.812 Y120.836 I-5.606 J11.227 E.1754
G1 X131.865 Y120.79 E.00835
G3 X134.167 Y119.31 I5.204 J5.563 E.32926
G1 X134.287 Y119.42 E.0194
G3 X134.664 Y119.804 I-8.876 J9.093 E.06442
G3 X133.148 Y122.167 I-7.139 J-2.912 E.33778
G3 X133.883 Y123.434 I-10.465 J6.918 E.1754
G1 X133.952 Y123.421 E.00836
G3 X136.686 Y123.29 I1.725 J7.42 E.32926
G1 X136.735 Y123.445 E.0194
G3 X136.869 Y123.966 I-12.24 J3.439 E.06442
G3 X134.375 Y125.254 I-4.727 J-6.092 E.33778
G3 X134.378 Y126.719 I-12.522 J.759 E.1754
G1 X134.444 Y126.742 E.00836
G3 X136.878 Y127.996 I-2.026 J6.919 E.32956
G1 X136.842 Y128.154 E.01937
G3 X136.698 Y128.673 I-12.598 J-3.222 E.06441
G3 X133.894 Y128.542 I-1.048 J-7.639 E.33778
G3 X133.164 Y129.812 I-11.227 J-5.606 E.1754
G1 X133.21 Y129.865 E.00835
G3 X134.69 Y132.167 I-5.563 J5.204 E.32926
G1 X134.58 Y132.287 E.0194
G3 X134.196 Y132.664 I-9.09 J-8.873 E.06442
G3 X131.833 Y131.148 I2.912 J-7.139 E.33778
G3 X130.566 Y131.883 I-6.918 J-10.466 E.1754
G1 X130.579 Y131.952 E.00836
G3 X130.71 Y134.686 I-7.42 J1.725 E.32926
G1 X130.555 Y134.735 E.0194
G3 X130.034 Y134.869 I-3.436 J-12.231 E.06442
G3 X128.746 Y132.375 I6.092 J-4.727 E.33778
G3 X127.281 Y132.378 I-.759 J-12.522 E.1754
G1 X127.258 Y132.444 E.00836
G3 X126.004 Y134.878 I-6.919 J-2.026 E.32956
G1 X125.846 Y134.842 E.01937
G3 X125.327 Y134.698 I3.222 J-12.598 E.06441
G3 X125.458 Y131.894 I7.639 J-1.048 E.33778
G3 X124.188 Y131.164 I5.605 J-11.225 E.1754
G1 X124.135 Y131.21 E.00836
G3 X121.833 Y132.69 I-5.203 J-5.563 E.32926
G1 X121.713 Y132.58 E.0194
G3 X121.336 Y132.196 I8.877 J-9.094 E.06441
G3 X122.852 Y129.833 I7.139 J2.912 E.33778
G3 X122.171 Y128.673 I10.466 J-6.918 E.16104
M204 S10000
; WIPE_START
G1 F24000
G1 X122.048 Y128.579 E-.22045
G1 X121.467 Y128.691 E-.84323
G1 X120.774 Y128.771 E-.99392
G1 X120.218 Y128.78 E-.79239
; WIPE_END
G1 E-.15 F1800
G1 X121.489 Y127.76 Z4.4 F30000
G1 Z4
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 1.04466
G1 F1877.301
G1 X121.119 Y127.86 E.05998
; LINE_WIDTH: 0.997248
G1 F1974.968
G1 X120.748 Y127.959 E.05701
; LINE_WIDTH: 0.973541
G1 F2027.711
G1 X119.577 Y128.304 E.17658
G1 X121.483 Y127.736 F30000
; LINE_WIDTH: 0.839236
G1 F2389.182
G1 X119.575 Y128.297 E.24414
G1 X119.573 Y128.291 F30000
; LINE_WIDTH: 0.666301
G1 F3000
G1 X121.481 Y127.729 E.1881
G1 X121.481 Y124.269 F30000
; LINE_WIDTH: 1.04465
G1 F1877.327
G1 X121.111 Y124.17 E.05997
; LINE_WIDTH: 0.997245
G1 F1974.974
G1 X120.74 Y124.071 E.05701
; LINE_WIDTH: 0.973542
G1 F2027.709
G1 X119.553 Y123.784 E.17659
G1 X119.555 Y123.777 F30000
; LINE_WIDTH: 0.839239
G1 F2389.174
G1 X121.488 Y124.245 E.24413
G1 X123.243 Y121.218 F30000
; LINE_WIDTH: 0.666304
G1 F3000
G1 X121.803 Y119.848 E.1881
G1 X121.798 Y119.853 F30000
; LINE_WIDTH: 0.839248
G1 F2389.145
G1 X123.238 Y121.224 E.24415
G1 X123.22 Y121.242 F30000
; LINE_WIDTH: 1.04467
G1 F1877.285
G1 X122.949 Y120.971 E.05998
; LINE_WIDTH: 0.997247
G1 F1974.97
G1 X122.677 Y120.699 E.05702
; LINE_WIDTH: 0.973536
G1 F2027.724
G1 X121.793 Y119.858 E.17658
; WIPE_START
G1 F24000
G1 X122.677 Y120.699 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X125.696 Y117.577 Z4.4 F30000
G1 Z4
G1 E3 F1800
; LINE_WIDTH: 0.973537
G1 F2027.72
G1 X126.041 Y118.748 E.17658
; LINE_WIDTH: 0.997245
G1 F1974.975
G1 X126.14 Y119.119 E.05701
; LINE_WIDTH: 1.04466
G1 F1877.311
G1 X126.24 Y119.489 E.05998
G1 X126.264 Y119.483 F30000
; LINE_WIDTH: 0.839245
G1 F2389.155
G1 X125.703 Y117.575 E.24414
G1 X125.709 Y117.573 F30000
; LINE_WIDTH: 0.666306
G1 F3000
G1 X126.271 Y119.481 E.1881
G1 X129.755 Y119.488 F30000
; LINE_WIDTH: 0.839241
G1 F2389.169
G1 X130.223 Y117.555 E.24413
G1 X130.23 Y117.557 F30000
; LINE_WIDTH: 0.666301
G1 F3000
G1 X129.763 Y119.49 E.18809
G1 X130.265 Y119.588 F30000
; LINE_WIDTH: 1.06063
G1 F1846.545
G1 X129.858 Y119.007 E.11284
G1 X129.893 Y118.873 E.02195
; LINE_WIDTH: 0.997245
G1 F1974.975
G1 X129.929 Y118.74 E.02052
; LINE_WIDTH: 0.96828
G1 F2039.8
G1 X130.216 Y117.553 E.17554
; WIPE_START
G1 F24000
G1 X129.929 Y118.74 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X134.142 Y119.793 Z4.4 F30000
G1 Z4
G1 E3 F1800
; LINE_WIDTH: 0.968285
G1 F2039.788
G1 X133.301 Y120.677 E.17554
; LINE_WIDTH: 0.99725
G1 F1974.963
G1 X133.203 Y120.775 E.02053
; LINE_WIDTH: 1.06063
G1 F1846.544
G1 X133.105 Y120.873 E.02195
G1 X132.4 Y120.813 E.11252
G1 X132.776 Y121.238 F30000
; LINE_WIDTH: 0.820918
G1 F2448.722
G1 X134.147 Y119.798 E.2382
G1 X134.152 Y119.803 F30000
; LINE_WIDTH: 0.649824
G1 F3000
G1 X132.782 Y121.243 E.18276
; WIPE_START
G1 F24000
G1 X134.152 Y119.803 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X136.423 Y123.696 Z4.4 F30000
G1 Z4
G1 E3 F1800
; LINE_WIDTH: 0.968284
G1 F2039.79
G1 X135.252 Y124.041 E.17554
; LINE_WIDTH: 0.997248
G1 F1974.968
G1 X135.119 Y124.076 E.02052
; LINE_WIDTH: 1.06063
G1 F1846.561
G1 X134.985 Y124.112 E.02195
G1 X134.404 Y123.707 E.11251
G1 X134.517 Y124.264 F30000
; LINE_WIDTH: 0.820922
G1 F2448.708
G1 X136.425 Y123.703 E.2382
G1 X136.427 Y123.709 F30000
; LINE_WIDTH: 0.64981
G1 F3000
G1 X134.519 Y124.271 E.18275
G1 X132.378 Y123.638 F30000
; LINE_WIDTH: 0.649307
G1 F3000
G1 X131.997 Y122.916 E.07501
; LINE_WIDTH: 0.652035
G1 X131.891 Y122.79 E.01519
; LINE_WIDTH: 0.694078
G1 F2959.372
G1 X131.786 Y122.663 E.01632
; LINE_WIDTH: 0.736121
G1 F2768.039
G1 X131.68 Y122.537 E.01745
; LINE_WIDTH: 0.764225
G1 F2653.362
G1 X131.575 Y122.41 E.01821
G1 X131.231 Y122.145 E.04803
; LINE_WIDTH: 0.686707
G1 F2995.674
G2 X129.803 Y121.312 I-4.565 J6.182 E.16213
; LINE_WIDTH: 0.725952
G1 F2812.01
G1 X129.569 Y121.213 E.02659
; LINE_WIDTH: 0.770916
G1 F2627.449
G2 X129.298 Y121.101 I-.952 J1.919 E.03275
; LINE_WIDTH: 0.773505
G1 F2617.557
G1 X129.045 Y121.07 E.02858
; LINE_WIDTH: 0.72751
G1 F2805.185
G2 X128.758 Y121.035 I-.788 J5.3 E.03017
; LINE_WIDTH: 0.686105
G1 F2998.68
G2 X127.139 Y121.047 I-.755 J7.485 E.1587
; LINE_WIDTH: 0.73551
G1 F2770.64
G1 X126.909 Y121.078 E.02462
; LINE_WIDTH: 0.779937
G1 F2593.299
G2 X126.601 Y121.138 I-.017 J.726 E.0358
; LINE_WIDTH: 0.758691
G1 F2675.185
G1 X126.367 Y121.239 E.02794
; LINE_WIDTH: 0.716998
G1 F2851.904
G2 X126.103 Y121.354 I2.001 J4.956 E.02961
; LINE_WIDTH: 0.686279
G1 F2997.81
G1 X125.62 Y121.595 E.05283
G2 X124.742 Y122.167 I4.304 J7.569 E.10261
; LINE_WIDTH: 0.723088
G1 F2824.651
G1 X124.714 Y122.188 E.00358
; LINE_WIDTH: 0.7443
G1 F2733.653
G1 X124.562 Y122.307 E.02068
; LINE_WIDTH: 0.781438
G1 F2587.704
G2 X124.309 Y122.552 I.559 J.833 E.04019
; LINE_WIDTH: 0.745123
G1 F2730.243
G1 X124.158 Y122.757 E.02736
; LINE_WIDTH: 0.70772
G1 F2894.454
G2 X123.989 Y122.99 I4.229 J3.253 E.02912
; LINE_WIDTH: 0.679458
G1 F3000
G2 X123.442 Y123.92 I5.341 J3.767 E.1045
; LINE_WIDTH: 0.692852
G1 F2965.35
G1 X123.337 Y124.151 E.02517
; LINE_WIDTH: 0.720967
G1 F2834.081
G2 X123.217 Y124.415 I4.816 J2.343 E.02997
; LINE_WIDTH: 0.753746
G1 F2694.993
G1 X123.161 Y124.557 E.01665
; LINE_WIDTH: 0.781634
G1 F2586.977
G2 X123.073 Y124.902 I.725 J.368 E.0407
; LINE_WIDTH: 0.751622
G1 F2703.589
G1 X123.069 Y124.938 E.00391
; LINE_WIDTH: 0.732818
G1 F2782.169
G1 X123.043 Y125.191 E.02684
; LINE_WIDTH: 0.683443
G1 F3000
G2 X123.019 Y126.556 I6.365 J.798 E.13317
; LINE_WIDTH: 0.699577
G1 F2932.855
G1 X123.045 Y126.809 E.02546
; LINE_WIDTH: 0.732007
G1 F2785.659
G2 X123.075 Y127.097 I5.355 J-.423 E.03058
; LINE_WIDTH: 0.763829
G1 F2654.913
M73 P73 R2
G1 X123.093 Y127.209 E.01251
; LINE_WIDTH: 0.776692
G1 F2605.481
G2 X123.215 Y127.586 I.9 J-.085 E.04496
; LINE_WIDTH: 0.738233
G1 F2759.076
G1 X123.229 Y127.618 E.00375
; LINE_WIDTH: 0.721767
G1 F2830.518
G1 X123.336 Y127.849 E.02637
; LINE_WIDTH: 0.682364
G1 F3000
G2 X124.009 Y129.037 I5.975 J-2.602 E.13292
; LINE_WIDTH: 0.707554
G1 F2895.228
G1 X124.159 Y129.242 E.0258
; LINE_WIDTH: 0.744318
G1 F2733.577
G2 X124.333 Y129.476 I4.417 J-3.089 E.03126
; LINE_WIDTH: 0.770196
G1 F2630.213
G1 X124.426 Y129.589 E.01635
G1 X124.713 Y129.813 E.04064
; LINE_WIDTH: 0.726096
G1 F2811.378
G1 X124.741 Y129.834 E.00361
; LINE_WIDTH: 0.690321
G1 F2977.762
G2 X125.507 Y130.339 I5.411 J-7.374 E.0904
; LINE_WIDTH: 0.682268
G1 F3000
G2 X126.133 Y130.659 I2.92 J-4.942 E.06843
; LINE_WIDTH: 0.716781
G1 F2852.883
G1 X126.367 Y130.759 E.0262
; LINE_WIDTH: 0.757908
G1 F2678.305
G2 X126.636 Y130.874 I2.248 J-4.914 E.03202
; LINE_WIDTH: 0.79027
G1 F2555.261
G1 X126.699 Y130.897 E.00765
; LINE_WIDTH: 0.778485
G1 F2598.736
G1 X126.919 Y130.926 E.02505
; LINE_WIDTH: 0.734783
G1 F2773.745
G2 X127.173 Y130.958 I.73 J-4.696 E.02707
; LINE_WIDTH: 0.686033
G1 F2999.04
G2 X128.791 Y130.96 I.82 J-7.354 E.15864
; LINE_WIDTH: 0.727257
G1 F2806.289
G1 X129.044 Y130.928 E.02665
; LINE_WIDTH: 0.772592
G1 F2621.037
G2 X129.334 Y130.888 I.005 J-1.016 E.03289
; LINE_WIDTH: 0.771682
G1 F2624.514
G1 X129.569 Y130.788 E.0285
; LINE_WIDTH: 0.726199
G1 F2810.928
G2 X129.834 Y130.675 I-1.973 J-4.984 E.0301
; LINE_WIDTH: 0.686172
G1 F2998.347
G1 X130.143 Y130.524 E.03365
G2 X131.23 Y129.854 I-3.175 J-6.361 E.12506
; LINE_WIDTH: 0.736523
G1 F2766.326
G1 X131.41 Y129.714 E.02416
; LINE_WIDTH: 0.777778
G1 F2601.393
G1 X131.59 Y129.575 E.02569
; LINE_WIDTH: 0.77773
G1 X131.692 Y129.453 E.01797
; LINE_WIDTH: 0.736378
G1 F2766.944
G1 X131.794 Y129.33 E.0169
; LINE_WIDTH: 0.695026
G1 F2954.768
G1 X131.896 Y129.207 E.01582
; LINE_WIDTH: 0.639718
G1 F3000
G1 X131.997 Y129.085 E.01439
G1 X132.379 Y128.357 E.07416
G1 X134.51 Y127.763 F30000
; LINE_WIDTH: 0.645796
G1 F3000
G1 X136.443 Y128.23 E.18145
G1 X136.445 Y128.223 F30000
; LINE_WIDTH: 0.820922
G1 F2448.709
G1 X134.512 Y127.755 E.2382
G1 X134.692 Y127.217 F30000
; LINE_WIDTH: 1.06061
G1 F1846.584
G1 X134.993 Y127.858 E.11251
G1 X135.127 Y127.893 E.02195
; LINE_WIDTH: 0.997243
G1 F1974.978
G1 X135.26 Y127.929 E.02052
; LINE_WIDTH: 0.968285
G1 F2039.788
G1 X136.447 Y128.216 E.17554
; WIPE_START
G1 F24000
G1 X135.26 Y127.929 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X134.207 Y132.142 Z4.4 F30000
G1 Z4
G1 E3 F1800
; LINE_WIDTH: 0.968282
G1 F2039.797
G1 X133.323 Y131.301 E.17553
; LINE_WIDTH: 0.997244
G1 F1974.977
G1 X133.225 Y131.203 E.02053
; LINE_WIDTH: 1.06064
G1 F1846.538
G1 X133.127 Y131.105 E.02196
G1 X133.187 Y130.4 E.11251
G1 X132.762 Y130.776 F30000
; LINE_WIDTH: 0.820921
G1 F2448.712
G1 X134.202 Y132.147 E.23821
G1 X134.197 Y132.152 F30000
; LINE_WIDTH: 0.649823
G1 F3000
G1 X132.757 Y130.782 E.18276
G1 X129.729 Y132.519 F30000
; LINE_WIDTH: 0.666305
G1 F3000
G1 X130.291 Y134.427 E.1881
G1 X130.297 Y134.425 F30000
; LINE_WIDTH: 0.820921
G1 F2448.713
G1 X129.736 Y132.517 E.2382
G1 X130.293 Y132.404 F30000
; LINE_WIDTH: 1.06063
G1 F1846.551
G1 X129.888 Y132.985 E.11252
G1 X129.924 Y133.119 E.02195
; LINE_WIDTH: 0.997248
G1 F1974.968
G1 X129.959 Y133.252 E.02053
; LINE_WIDTH: 0.968285
G1 F2039.788
G1 X130.304 Y134.423 E.17554
; WIPE_START
G1 F24000
G1 X129.959 Y133.252 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X125.784 Y134.447 Z4.4 F30000
G1 Z4
G1 E3 F1800
; LINE_WIDTH: 0.973542
G1 F2027.709
G1 X126.071 Y133.26 E.17658
; LINE_WIDTH: 0.997245
G1 F1974.975
G1 X126.17 Y132.889 E.05701
; LINE_WIDTH: 1.04465
G1 F1877.33
G1 X126.269 Y132.519 E.05997
G1 X126.245 Y132.512 F30000
; LINE_WIDTH: 0.839238
G1 F2389.177
G1 X125.777 Y134.445 E.24413
G1 X125.77 Y134.443 F30000
; LINE_WIDTH: 0.666298
G1 F3000
G1 X126.237 Y132.51 E.18809
G1 X123.218 Y130.757 F30000
; LINE_WIDTH: 0.666304
G1 F3000
G1 X121.848 Y132.197 E.18811
G1 X121.853 Y132.202 F30000
; LINE_WIDTH: 0.839246
G1 F2389.151
G1 X123.224 Y130.762 E.24415
G1 X123.242 Y130.78 F30000
; LINE_WIDTH: 1.04468
G1 F1877.271
G1 X122.971 Y131.051 E.05998
; LINE_WIDTH: 0.997254
G1 F1974.955
G1 X122.699 Y131.323 E.05702
; LINE_WIDTH: 0.973542
G1 F2027.708
G1 X121.858 Y132.207 E.17658
; WIPE_START
G1 F24000
G1 X122.699 Y131.323 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X129.352 Y127.582 Z4.4 F30000
G1 X132.183 Y125.991 Z4.4
G1 Z4
G1 E3 F1800
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.81487
G1 F2469.038
G2 X132.173 Y127.426 I81.524 J1.325 E.17051
G1 X132.684 Y127.695 E.0687
G1 X132.892 Y127.3 E.053
G2 X132.892 Y124.773 I-33.617 J-1.255 E.30034
G1 X132.85 Y124.608 E.02014
G1 X132.685 Y124.298 E.0417
G1 X132.171 Y124.57 E.06906
G2 X132.182 Y125.871 I66.158 J.109 E.15459
; CHANGE_LAYER
; Z_HEIGHT: 4.4
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X132.171 Y124.57 E-1.85409
G1 X132.685 Y124.298 E-.82827
G1 X132.741 Y124.402 E-.16763
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 11/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L11
M991 S0 P10 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z4.4 I.8 J-.917 P1  F30000
G1 X131.344 Y123.183 Z4.4
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2451.784
G1 X131.444 Y123.276 E.01641
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X127.853 Y121.661 I-2.779 J-3.338 E1.97551
G3 X130.78 Y122.66 I.134 J4.397 E.37815
G1 X131.256 Y123.101 E.07762
G1 X130.71 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X127.858 Y122.396 I-2.309 J-2.774 E1.63908
G1 X128.17 Y122.393 E.03732
G3 X130.627 Y123.509 I-.217 J3.743 E.33037
M204 S10000
; WIPE_START
G1 F24000
G1 X130.661 Y125.509 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.338 Y127.66 Z4.8 F30000
G1 X122.479 Y127.912 Z4.8
G1 Z4.4
G1 E3 F1800
; FEATURE: Inner wall
G1 F2451.784
G1 X121.956 Y128.028 E.06408
G1 X121.838 Y127.636 E.04897
G1 X122.422 Y127.413 E.07478
G3 X122.368 Y124.928 I13.869 J-1.547 E.29772
G1 X121.752 Y124.735 E.07724
G1 X121.846 Y124.336 E.04897
G1 X122.463 Y124.435 E.07478
G3 X123.658 Y122.256 I12.783 J5.594 E.29772
G1 X123.222 Y121.78 E.07724
G1 X123.502 Y121.482 E.04897
G1 X123.988 Y121.876 E.07478
G3 X126.112 Y120.586 I8.274 J11.237 E.29772
G1 X125.972 Y119.956 E.07724
G1 X126.364 Y119.838 E.04897
G1 X126.587 Y120.422 E.07478
G3 X129.072 Y120.368 I1.547 J13.869 E.29772
G1 X129.265 Y119.752 E.07724
G1 X129.664 Y119.846 E.04897
G1 X129.565 Y120.463 E.07478
G3 X131.744 Y121.658 I-5.594 J12.783 E.29772
G1 X132.22 Y121.222 E.07725
G1 X132.518 Y121.502 E.04897
G1 X132.124 Y121.988 E.07478
G3 X133.414 Y124.112 I-11.236 J8.273 E.29772
G1 X134.044 Y123.972 E.07724
G1 X134.162 Y124.364 E.04897
G1 X133.578 Y124.587 E.07478
G3 X133.632 Y127.072 I-13.869 J1.547 E.29772
G1 X134.248 Y127.265 E.07724
G1 X134.154 Y127.664 E.04897
G1 X133.537 Y127.565 E.07478
G3 X132.342 Y129.744 I-12.784 J-5.595 E.29772
G1 X132.778 Y130.22 E.07724
G1 X132.498 Y130.518 E.04897
G1 X132.012 Y130.124 E.07478
G3 X129.888 Y131.414 I-8.274 J-11.238 E.29772
G1 X130.028 Y132.044 E.07724
G1 X129.636 Y132.162 E.04897
G1 X129.413 Y131.578 E.07478
G3 X126.928 Y131.632 I-1.547 J-13.869 E.29772
G1 X126.735 Y132.248 E.07724
G1 X126.336 Y132.154 E.04897
G1 X126.435 Y131.537 E.07478
G3 X124.256 Y130.342 I5.594 J-12.783 E.29772
G1 X123.78 Y130.778 E.07725
G1 X123.482 Y130.498 E.04897
G1 X123.876 Y130.012 E.07478
G3 X122.591 Y127.897 I11.237 J-8.274 E.29652
G1 X122.199 Y128.726 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X122.119 Y128.744 E.00984
G3 X119.391 Y128.951 I-1.932 J-7.388 E.3291
G3 X119.341 Y128.796 I1.747 J-.655 E.01946
G3 X119.191 Y128.28 I5.836 J-1.974 E.06432
G3 X121.65 Y126.922 I4.889 J5.949 E.33798
G3 X121.613 Y125.461 I10.519 J-.995 E.1751
G1 X121.535 Y125.436 E.00984
G3 X119.069 Y124.251 I1.924 J-7.162 E.3292
G3 X119.103 Y124.092 I1.841 J.307 E.01946
G3 X119.231 Y123.57 I6.041 J1.208 E.06432
G3 X122.039 Y123.624 I1.26 J7.596 E.33798
G3 X122.739 Y122.339 I9.606 J4.398 E.1751
G1 X122.683 Y122.279 E.00984
G3 X121.14 Y120.02 I5.432 J-5.367 E.3291
G3 X121.249 Y119.899 I1.441 J1.186 E.01946
G3 X121.621 Y119.511 I4.627 J4.066 E.06432
G3 X124.026 Y120.962 I-2.707 J7.208 E.33798
G3 X125.274 Y120.199 I6.121 J8.612 E.1751
G1 X125.256 Y120.119 E.00984
G3 X125.049 Y117.391 I7.388 J-1.932 E.3291
G3 X125.204 Y117.341 I.655 J1.748 E.01946
G3 X125.72 Y117.191 I1.974 J5.835 E.06432
G3 X127.078 Y119.65 I-5.949 J4.889 E.33798
G3 X128.539 Y119.613 I.995 J10.519 E.1751
G1 X128.564 Y119.535 E.00984
G3 X129.749 Y117.069 I7.144 J1.915 E.32922
G3 X129.908 Y117.103 I-.313 J1.87 E.01946
G3 X130.43 Y117.231 I-1.208 J6.041 E.06432
G3 X130.376 Y120.039 I-7.596 J1.26 E.33798
G3 X131.661 Y120.739 I-4.398 J9.607 E.1751
G1 X131.721 Y120.683 E.00984
G3 X133.98 Y119.14 I5.367 J5.432 E.3291
G3 X134.101 Y119.249 I-1.186 J1.441 E.01946
G3 X134.489 Y119.621 I-4.067 J4.628 E.06432
G3 X133.038 Y122.026 I-7.208 J-2.707 E.33798
G3 X133.801 Y123.274 I-8.612 J6.121 E.1751
G1 X133.881 Y123.256 E.00984
G3 X136.609 Y123.049 I1.932 J7.388 E.3291
G3 X136.659 Y123.204 I-1.748 J.655 E.01946
G3 X136.809 Y123.72 I-5.835 J1.974 E.06432
G3 X134.35 Y125.078 I-4.889 J-5.948 E.33798
G3 X134.387 Y126.539 I-10.519 J.995 E.1751
G1 X134.465 Y126.564 E.00984
G3 X136.931 Y127.749 I-1.924 J7.162 E.3292
G3 X136.897 Y127.908 I-1.841 J-.307 E.01946
G3 X136.769 Y128.43 I-6.041 J-1.208 E.06432
G3 X133.961 Y128.376 I-1.26 J-7.596 E.33798
G3 X133.261 Y129.661 I-9.607 J-4.398 E.1751
G1 X133.317 Y129.721 E.00984
G3 X134.86 Y131.98 I-5.432 J5.367 E.3291
G3 X134.751 Y132.101 I-1.441 J-1.186 E.01946
G3 X134.379 Y132.489 I-4.628 J-4.067 E.06432
G3 X131.974 Y131.038 I2.707 J-7.208 E.33798
G3 X130.726 Y131.801 I-6.121 J-8.613 E.1751
G1 X130.744 Y131.881 E.00984
G3 X130.951 Y134.609 I-7.388 J1.932 E.3291
G3 X130.796 Y134.659 I-.655 J-1.748 E.01946
G3 X130.28 Y134.809 I-1.974 J-5.835 E.06432
G3 X128.922 Y132.35 I5.949 J-4.889 E.33798
G3 X127.461 Y132.387 I-.995 J-10.519 E.1751
G1 X127.436 Y132.465 E.00984
G3 X126.251 Y134.931 I-7.162 J-1.924 E.3292
G3 X126.092 Y134.897 I.307 J-1.842 E.01946
G3 X125.57 Y134.769 I1.208 J-6.041 E.06432
G3 X125.624 Y131.961 I7.596 J-1.26 E.33798
G3 X124.339 Y131.261 I4.398 J-9.606 E.1751
G1 X124.279 Y131.317 E.00984
G3 X122.02 Y132.86 I-5.367 J-5.432 E.3291
G3 X121.899 Y132.751 I1.186 J-1.441 E.01946
G3 X121.511 Y132.379 I4.067 J-4.628 E.06432
G3 X122.962 Y129.974 I7.208 J2.707 E.33798
G3 X122.255 Y128.832 I8.613 J-6.121 E.16074
M204 S10000
; WIPE_START
G1 F24000
G1 X122.119 Y128.744 E-.23133
M73 P74 R2
G1 X121.544 Y128.872 E-.83848
G1 X120.854 Y128.971 E-.99375
G1 X120.303 Y128.994 E-.78645
; WIPE_END
G1 E-.15 F1800
G1 X121.546 Y127.939 Z4.8 F30000
G1 Z4.4
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 1.0458
G1 F1875.08
G1 X121.176 Y128.05 E.06048
; LINE_WIDTH: 0.997576
G1 F1974.258
G1 X120.805 Y128.16 E.05744
; LINE_WIDTH: 0.973465
G1 F2027.885
G1 X119.644 Y128.538 E.17662
G1 X121.539 Y127.915 F30000
; LINE_WIDTH: 0.839175
G1 F2389.379
G1 X119.642 Y128.53 E.24485
G1 X119.64 Y128.524 F30000
; LINE_WIDTH: 0.666257
G1 F3000
G1 X121.537 Y127.907 E.18866
G1 X121.441 Y124.452 F30000
; LINE_WIDTH: 1.0458
G1 F1875.079
G1 X121.065 Y124.363 E.06048
; LINE_WIDTH: 0.997577
G1 F1974.256
G1 X120.689 Y124.273 E.05744
; LINE_WIDTH: 0.973465
G1 F2027.884
G1 X119.495 Y124.02 E.17662
; WIPE_START
G1 F24000
G1 X120.689 Y124.273 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X121.625 Y120.032 Z4.8 F30000
G1 Z4.4
G1 E3 F1800
; LINE_WIDTH: 0.97347
G1 F2027.874
G1 X122.532 Y120.849 E.17662
; LINE_WIDTH: 0.997581
G1 F1974.247
G1 X122.813 Y121.115 E.05744
; LINE_WIDTH: 1.0458
G1 F1875.071
G1 X123.094 Y121.38 E.06048
G1 X123.111 Y121.362 F30000
; LINE_WIDTH: 0.839172
G1 F2389.386
G1 X121.63 Y120.027 E.24485
G1 X121.634 Y120.022 F30000
; LINE_WIDTH: 0.666255
G1 F3000
G1 X123.117 Y121.356 E.18866
; WIPE_START
G1 F24000
G1 X121.634 Y120.022 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X125.462 Y117.644 Z4.8 F30000
G1 Z4.4
G1 E3 F1800
; LINE_WIDTH: 0.973462
G1 F2027.891
G1 X125.84 Y118.805 E.17662
; LINE_WIDTH: 0.997574
G1 F1974.261
G1 X125.95 Y119.176 E.05744
; LINE_WIDTH: 1.0458
G1 F1875.081
G1 X126.061 Y119.546 E.06048
G1 X126.085 Y119.539 F30000
; LINE_WIDTH: 0.83918
G1 F2389.363
G1 X125.47 Y117.642 E.24485
G1 X125.476 Y117.64 F30000
; LINE_WIDTH: 0.666251
G1 F3000
G1 X126.093 Y119.537 E.18866
G1 X129.566 Y119.446 F30000
; LINE_WIDTH: 0.839943
G1 F2386.945
G1 X129.993 Y117.498 E.24508
G1 X129.994 Y117.498 F30000
; LINE_WIDTH: 0.666255
G1 F3000
G1 X129.58 Y119.449 E.18866
G1 X130.085 Y119.533 F30000
; LINE_WIDTH: 1.05976
G1 F1848.198
G1 X129.662 Y118.964 E.11259
G1 X129.696 Y118.815 E.02418
; LINE_WIDTH: 0.995994
G1 F1977.69
G1 X130.025 Y117.505 E.20038
; WIPE_START
G1 F24000
G1 X129.696 Y118.815 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X133.968 Y119.625 Z4.8 F30000
G1 Z4.4
G1 E3 F1800
; LINE_WIDTH: 0.96822
G1 F2039.94
G1 X133.151 Y120.532 E.17558
; LINE_WIDTH: 0.997582
G1 F1974.244
G1 X133.054 Y120.634 E.02088
; LINE_WIDTH: 1.06192
G1 F1844.105
G1 X132.958 Y120.736 E.02235
G1 X132.25 Y120.696 E.1127
G1 X132.638 Y121.111 F30000
; LINE_WIDTH: 0.820879
G1 F2448.852
G1 X133.973 Y119.63 E.2389
G1 X133.978 Y119.634 F30000
; LINE_WIDTH: 0.649721
G1 F3000
G1 X132.644 Y121.117 E.18328
G1 X131.839 Y122.222 F30000
; LINE_WIDTH: 0.788661
G1 F2561.111
G1 X132.261 Y123.663 E.17202
G1 X132.382 Y123.633 F30000
; LINE_WIDTH: 0.640443
G1 F3000
G1 X131.993 Y122.921 E.0734
; LINE_WIDTH: 0.639765
G1 X131.871 Y122.78 E.01679
; LINE_WIDTH: 0.681571
G1 X131.75 Y122.639 E.01805
; LINE_WIDTH: 0.723377
G1 F2823.369
G1 X131.629 Y122.498 E.01932
; LINE_WIDTH: 0.757594
G1 F2679.554
G2 X131.231 Y122.144 I-1.043 J.774 E.05862
; LINE_WIDTH: 0.685058
G1 F3000
G2 X129.801 Y121.32 I-4.196 J5.624 E.16162
; LINE_WIDTH: 0.706528
G1 F2900.011
G1 X129.565 Y121.224 E.02576
; LINE_WIDTH: 0.742958
G1 F2739.237
G2 X129.294 Y121.117 I-2.131 J4.946 E.03118
; LINE_WIDTH: 0.774108
G1 F2615.262
G1 X129.216 Y121.09 E.00927
; LINE_WIDTH: 0.765735
G1 F2647.472
G1 X129.004 Y121.064 E.02369
; LINE_WIDTH: 0.726358
G1 F2810.229
G2 X128.758 Y121.034 I-.67 J4.546 E.02583
; LINE_WIDTH: 0.68345
G1 F3000
G2 X127.141 Y121.056 I-.72 J6.657 E.1579
; LINE_WIDTH: 0.71565
G1 F2858.007
G1 X126.889 Y121.093 E.02615
; LINE_WIDTH: 0.756662
G1 F2683.276
G2 X126.598 Y121.138 I.634 J5.106 E.03225
; LINE_WIDTH: 0.761031
G1 F2665.917
G1 X126.365 Y121.239 E.02789
; LINE_WIDTH: 0.719109
G1 F2842.398
G2 X126.102 Y121.353 I1.998 J4.936 E.02958
; LINE_WIDTH: 0.68337
G1 F3000
G2 X124.721 Y122.195 I2.865 J6.253 E.1579
; LINE_WIDTH: 0.724424
G1 F2818.739
G1 X124.538 Y122.343 E.02449
; LINE_WIDTH: 0.765622
G1 F2647.911
G2 X124.308 Y122.551 I.377 J.65 E.03463
; LINE_WIDTH: 0.747654
G1 F2719.8
G1 X124.157 Y122.756 E.02747
; LINE_WIDTH: 0.709811
G1 F2884.752
G2 X123.988 Y122.989 I4.234 J3.251 E.02923
; LINE_WIDTH: 0.684107
G1 F3000
G2 X123.228 Y124.418 I5.774 J3.99 E.15815
; LINE_WIDTH: 0.732333
G1 F2784.256
G1 X123.159 Y124.601 E.02061
; LINE_WIDTH: 0.767456
G1 F2640.786
G2 X123.068 Y124.938 I.945 J.438 E.03896
; LINE_WIDTH: 0.735232
G1 F2771.825
G1 X123.042 Y125.191 E.02694
; LINE_WIDTH: 0.68742
G1 F2992.124
G2 X123.082 Y127.06 I6.686 J.791 E.18389
; LINE_WIDTH: 0.723185
G1 F2824.221
G1 X123.087 Y127.094 E.00358
; LINE_WIDTH: 0.740877
G1 F2747.941
G1 X123.114 Y127.248 E.01665
; LINE_WIDTH: 0.765414
G1 F2648.722
G2 X123.228 Y127.619 I1.442 J-.24 E.04311
; LINE_WIDTH: 0.724048
G1 F2820.402
G1 X123.335 Y127.85 E.02646
; LINE_WIDTH: 0.681577
G1 F3000
G2 X124.013 Y129.033 I5.528 J-2.382 E.1327
; LINE_WIDTH: 0.692738
G1 F2965.906
G1 X124.166 Y129.236 E.02516
; LINE_WIDTH: 0.721028
G1 F2833.809
G2 X124.342 Y129.466 I4.343 J-3.137 E.02997
; LINE_WIDTH: 0.760495
G1 F2668.032
G2 X124.712 Y129.814 I1.017 J-.71 E.05627
; LINE_WIDTH: 0.728481
G1 F2800.944
G1 X124.74 Y129.835 E.00364
; LINE_WIDTH: 0.694076
G1 F2959.382
G2 X125.393 Y130.271 I4.565 J-6.118 E.07786
; LINE_WIDTH: 0.678036
G1 F3000
G1 X125.648 Y130.419 E.02847
G2 X126.135 Y130.653 I11.666 J-23.763 E.05215
; LINE_WIDTH: 0.69952
G1 F2933.128
G1 X126.371 Y130.749 E.02545
; LINE_WIDTH: 0.732128
G1 F2785.139
G2 X126.64 Y130.859 I2.16 J-4.918 E.03058
; LINE_WIDTH: 0.757543
G1 F2679.758
G1 X126.784 Y130.909 E.01674
G1 X127.139 Y130.956 E.03916
; LINE_WIDTH: 0.684886
G1 F3000
G2 X128.79 Y130.953 I.813 J-6.98 E.16156
; LINE_WIDTH: 0.707542
G1 F2895.282
G1 X129.042 Y130.917 E.0258
; LINE_WIDTH: 0.744487
G1 F2732.879
G2 X129.33 Y130.875 I-.633 J-5.353 E.03127
; LINE_WIDTH: 0.774849
G1 F2612.449
G1 X129.402 Y130.861 E.00822
; LINE_WIDTH: 0.765207
G1 F2649.528
G1 X129.603 Y130.775 E.02419
; LINE_WIDTH: 0.725466
G1 F2814.146
G2 X129.835 Y130.676 I-1.728 J-4.35 E.02628
; LINE_WIDTH: 0.683397
G1 F3000
G2 X131.223 Y129.847 I-2.722 J-6.138 E.15789
; LINE_WIDTH: 0.717984
G1 F2847.454
G1 X131.435 Y129.679 E.02784
; LINE_WIDTH: 0.75866
G1 F2675.311
G1 X131.646 Y129.51 E.02963
; LINE_WIDTH: 0.754997
G1 F2689.955
G1 X131.763 Y129.369 E.02005
; LINE_WIDTH: 0.706997
G1 F2897.82
G1 X131.881 Y129.227 E.01861
; LINE_WIDTH: 0.643507
G1 F3000
G1 X131.998 Y129.085 E.01671
G1 X132.394 Y128.33 E.07756
G1 X132.883 Y130.644 F30000
; LINE_WIDTH: 0.649721
G1 F3000
G1 X134.366 Y131.978 E.18328
G1 X134.37 Y131.973 F30000
; LINE_WIDTH: 0.820879
G1 F2448.854
G1 X132.889 Y130.638 E.2389
G1 X133.304 Y130.25 F30000
; LINE_WIDTH: 1.06193
G1 F1844.098
G1 X133.264 Y130.958 E.11269
G1 X133.366 Y131.054 E.02236
; LINE_WIDTH: 0.997578
G1 F1974.253
G1 X133.468 Y131.151 E.02088
; LINE_WIDTH: 0.968216
G1 F2039.948
G1 X134.375 Y131.968 E.17557
; WIPE_START
G1 F24000
G1 X133.468 Y131.151 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X130.538 Y134.356 Z4.8 F30000
G1 Z4.4
G1 E3 F1800
; LINE_WIDTH: 0.968213
G1 F2039.956
G1 X130.16 Y133.195 E.17558
; LINE_WIDTH: 0.997579
G1 F1974.251
G1 X130.12 Y133.06 E.02088
; LINE_WIDTH: 1.06193
G1 F1844.096
G1 X130.08 Y132.925 E.02236
G1 X130.468 Y132.333 E.11271
G1 X129.915 Y132.461 F30000
; LINE_WIDTH: 0.820874
G1 F2448.87
G1 X130.53 Y134.358 E.2389
G1 X130.524 Y134.36 F30000
; LINE_WIDTH: 0.649724
G1 F3000
G1 X129.907 Y132.463 E.18328
G1 X126.452 Y132.559 F30000
; LINE_WIDTH: 1.0458
G1 F1875.085
G1 X126.363 Y132.935 E.06047
; LINE_WIDTH: 0.997577
G1 F1974.255
G1 X126.273 Y133.311 E.05744
; LINE_WIDTH: 0.973465
G1 F2027.885
G1 X126.02 Y134.505 E.17662
; WIPE_START
G1 F24000
G1 X126.273 Y133.311 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.356 Y130.883 Z4.8 F30000
G1 Z4.4
G1 E3 F1800
; LINE_WIDTH: 0.666255
G1 F3000
G1 X122.022 Y132.366 E.18865
G1 X122.027 Y132.37 F30000
; LINE_WIDTH: 0.839187
G1 F2389.339
G1 X123.362 Y130.889 E.24485
G1 X123.38 Y130.906 F30000
; LINE_WIDTH: 1.0458
G1 F1875.089
G1 X123.115 Y131.187 E.06048
; LINE_WIDTH: 0.997574
G1 F1974.262
G1 X122.849 Y131.468 E.05744
; LINE_WIDTH: 0.973463
G1 F2027.889
G1 X122.032 Y132.375 E.17662
; WIPE_START
G1 F24000
G1 X122.849 Y131.468 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X130.244 Y129.579 Z4.8 F30000
G1 X136.505 Y127.98 Z4.8
G1 Z4.4
G1 E3 F1800
; LINE_WIDTH: 0.96669
G1 F2043.482
G1 X135.311 Y127.727 E.17527
; LINE_WIDTH: 0.997578
G1 F1974.253
G1 X135.174 Y127.694 E.02088
; LINE_WIDTH: 1.06193
G1 F1844.092
G1 X135.037 Y127.662 E.02236
G1 X134.719 Y127.029 E.11271
G1 X132.183 Y125.853 F30000
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.810871
G1 F2482.654
G2 X132.174 Y127.39 I118.657 J1.402 E.18156
G1 X132.681 Y127.655 E.06755
G1 X132.898 Y127.209 E.05867
G2 X132.924 Y125.828 I-237.876 J-5.145 E.16328
G1 X132.868 Y124.757 E.12666
G1 X132.827 Y124.54 E.02613
G1 X132.679 Y124.291 E.03421
G1 X132.164 Y124.573 E.06941
G2 X132.18 Y125.733 I33.322 J.105 E.13719
G1 X134.463 Y124.093 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 0.649725
G1 F3000
G1 X136.36 Y123.476 E.18328
G1 X136.358 Y123.47 F30000
; LINE_WIDTH: 0.820875
G1 F2448.866
G1 X134.461 Y124.085 E.2389
G1 X134.333 Y123.532 F30000
; LINE_WIDTH: 1.06193
G1 F1844.092
G1 X134.925 Y123.92 E.11272
G1 X135.06 Y123.88 E.02236
; LINE_WIDTH: 0.99758
G1 F1974.249
G1 X135.195 Y123.84 E.02088
; LINE_WIDTH: 0.968213
G1 F2039.955
G1 X136.356 Y123.463 E.17557
; CHANGE_LAYER
; Z_HEIGHT: 4.8
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X135.195 Y123.84 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 12/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L12
M991 S0 P11 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z4.8 I.205 J-1.2 P1  F30000
G1 X131.344 Y123.183 Z4.8
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2451.784
G1 X131.444 Y123.276 E.01639
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X127.825 Y121.662 I-2.776 J-3.339 E1.97142
G3 X130.78 Y122.66 I.159 J4.402 E.38147
G1 X131.256 Y123.101 E.07764
G1 X130.71 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X130.71 Y123.596 E.00007
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X127.83 Y122.396 I-2.306 J-2.775 E1.63504
G1 X128.17 Y122.393 E.04062
G3 X130.312 Y123.223 I-.217 J3.743 E.27931
G1 X130.622 Y123.514 E.05092
M204 S10000
; WIPE_START
G1 F24000
G1 X130.71 Y123.596 E-.17187
G1 X130.71 Y125.476 E-2.67813
; WIPE_END
G1 E-.15 F1800
G1 X123.43 Y127.77 Z5.2 F30000
G1 X122.522 Y128.056 Z5.2
G1 Z4.8
G1 E3 F1800
; FEATURE: Inner wall
G1 F2451.784
G1 X122.068 Y128.177 E.05621
G1 X121.936 Y127.787 E.04936
G1 X122.469 Y127.566 E.06914
G3 X122.328 Y125.068 I14.077 J-2.051 E.29968
G1 X121.774 Y124.92 E.06862
G1 X121.855 Y124.515 E.04936
G1 X122.428 Y124.591 E.06914
G3 X123.554 Y122.357 I13.216 J5.262 E.29968
G1 X123.148 Y121.951 E.06862
G1 X123.421 Y121.641 E.04936
G1 X123.879 Y121.993 E.06914
G3 X125.971 Y120.622 I8.815 J11.166 E.29968
G1 X125.823 Y120.068 E.06861
G1 X126.213 Y119.936 E.04936
G1 X126.434 Y120.469 E.06914
G3 X128.932 Y120.328 I2.051 J14.077 E.29968
G1 X129.08 Y119.774 E.06862
G1 X129.485 Y119.855 E.04936
G1 X129.409 Y120.428 E.06915
G3 X131.643 Y121.554 I-5.262 J13.217 E.29968
G1 X132.049 Y121.148 E.06862
M73 P75 R2
G1 X132.359 Y121.421 E.04936
G1 X132.007 Y121.879 E.06914
G3 X133.378 Y123.971 I-11.167 J8.815 E.29968
G1 X133.932 Y123.823 E.06862
G1 X134.065 Y124.213 E.04936
G1 X133.531 Y124.434 E.06914
G3 X133.672 Y126.932 I-14.077 J2.051 E.29968
G1 X134.226 Y127.08 E.06862
G1 X134.145 Y127.485 E.04936
G1 X133.572 Y127.409 E.06915
G3 X132.446 Y129.643 I-13.217 J-5.262 E.29968
G1 X132.852 Y130.049 E.06862
G1 X132.579 Y130.359 E.04936
G1 X132.121 Y130.007 E.06914
G3 X130.029 Y131.378 I-8.815 J-11.167 E.29968
G1 X130.177 Y131.932 E.06862
G1 X129.787 Y132.065 E.04936
G1 X129.566 Y131.531 E.06914
G3 X127.068 Y131.672 I-2.051 J-14.077 E.29968
G1 X126.92 Y132.226 E.06862
G1 X126.515 Y132.145 E.04936
G1 X126.591 Y131.572 E.06914
G3 X124.357 Y130.446 I5.262 J-13.216 E.29968
G1 X123.951 Y130.852 E.06862
G1 X123.641 Y130.579 E.04936
G1 X123.993 Y130.121 E.06914
G3 X122.63 Y128.044 I11.166 J-8.815 E.29773
G1 X122.27 Y128.883 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X122.2 Y128.902 E.00867
G3 X119.478 Y129.19 I-2.105 J-6.883 E.32959
G1 X119.422 Y129.036 E.01959
G3 X119.256 Y128.525 I13.29 J-4.597 E.06434
G3 X121.68 Y127.098 I5.04 J5.791 E.33848
G3 X121.596 Y125.632 I9.922 J-1.302 E.17582
G1 X121.526 Y125.613 E.00867
G3 X119.025 Y124.5 I1.673 J-7.13 E.32956
G1 X119.053 Y124.34 E.01946
G3 X119.165 Y123.814 I13.804 J2.663 E.06434
G3 X121.978 Y123.791 I1.47 J7.535 E.33848
G3 X122.638 Y122.479 I9.243 J3.833 E.17582
G1 X122.587 Y122.428 E.00867
G3 X120.976 Y120.214 I4.908 J-5.264 E.32959
G1 X121.082 Y120.089 E.01959
G3 X121.442 Y119.69 I10.619 J9.204 E.06434
G3 X123.889 Y121.076 I-2.495 J7.26 E.33848
G3 X125.117 Y120.27 I6.088 J7.942 E.17582
G1 X125.098 Y120.2 E.00867
G3 X124.81 Y117.478 I6.883 J-2.105 E.32959
G1 X124.964 Y117.422 E.01959
G3 X125.475 Y117.256 I4.597 J13.289 E.06434
G3 X126.902 Y119.68 I-5.791 J5.04 E.33848
G3 X128.368 Y119.596 I1.302 J9.921 E.17582
G1 X128.387 Y119.526 E.00867
G3 X129.498 Y117.025 I7.139 J1.674 E.32938
G1 X129.659 Y117.054 E.01962
G3 X130.186 Y117.165 I-2.436 J12.798 E.06437
G3 X130.209 Y119.978 I-7.535 J1.47 E.33848
G3 X131.521 Y120.638 I-3.833 J9.243 E.17582
G1 X131.572 Y120.587 E.00867
G3 X133.786 Y118.976 I5.264 J4.908 E.32959
G1 X133.911 Y119.082 E.01959
G3 X134.31 Y119.442 I-9.204 J10.619 E.06434
G3 X132.924 Y121.889 I-7.26 J-2.495 E.33848
G3 X133.73 Y123.117 I-7.942 J6.089 E.17582
G1 X133.8 Y123.098 E.00867
G3 X136.522 Y122.81 I2.105 J6.883 E.32959
G1 X136.578 Y122.964 E.01959
G3 X136.744 Y123.475 I-13.29 J4.597 E.06434
G3 X134.32 Y124.902 I-5.04 J-5.791 E.33848
G3 X134.404 Y126.368 I-9.921 J1.302 E.17582
G1 X134.474 Y126.387 E.00867
G3 X136.975 Y127.5 I-1.674 J7.13 E.32956
G1 X136.947 Y127.66 E.01946
G3 X136.835 Y128.186 I-13.801 J-2.662 E.06434
G3 X134.022 Y128.209 I-1.47 J-7.535 E.33848
G3 X133.362 Y129.521 I-9.243 J-3.834 E.17582
G1 X133.413 Y129.572 E.00867
G3 X135.024 Y131.786 I-4.908 J5.264 E.32959
G1 X134.918 Y131.911 E.01959
G3 X134.558 Y132.31 I-10.619 J-9.204 E.06434
G3 X132.111 Y130.924 I2.495 J-7.26 E.33848
G3 X130.883 Y131.73 I-6.089 J-7.942 E.17582
G1 X130.902 Y131.8 E.00867
G3 X131.19 Y134.522 I-6.883 J2.105 E.32959
G1 X131.036 Y134.578 E.01959
G3 X130.525 Y134.744 I-4.597 J-13.29 E.06434
G3 X129.098 Y132.32 I5.791 J-5.04 E.33848
G3 X127.632 Y132.404 I-1.302 J-9.921 E.17582
G1 X127.613 Y132.474 E.00867
G3 X126.5 Y134.975 I-7.13 J-1.674 E.32956
G1 X126.34 Y134.947 E.01946
G3 X125.814 Y134.835 I2.662 J-13.801 E.06434
G3 X125.791 Y132.022 I7.535 J-1.47 E.33848
G3 X124.479 Y131.362 I3.833 J-9.243 E.17582
G1 X124.428 Y131.413 E.00867
G3 X122.214 Y133.024 I-5.264 J-4.908 E.32959
G1 X122.089 Y132.918 E.01959
G3 X121.69 Y132.558 I9.206 J-10.621 E.06434
G3 X123.076 Y130.111 I7.26 J2.495 E.33848
G3 X122.329 Y128.988 I7.942 J-6.088 E.16146
M204 S10000
; WIPE_START
G1 F24000
G1 X122.2 Y128.902 E-.22067
G1 X121.628 Y129.05 E-.84244
G1 X120.938 Y129.169 E-.99765
G1 X120.386 Y129.208 E-.78924
; WIPE_END
G1 E-.15 F1800
G1 X121.654 Y128.1 Z5.2 F30000
G1 Z4.8
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 1.08004
G1 F1810.499
G2 X121.137 Y128.271 I3.223 J10.618 E.08819
; LINE_WIDTH: 1.04725
G1 F1872.245
G1 X121.002 Y128.315 E.02231
; LINE_WIDTH: 0.998389
G1 F1972.498
G1 X120.867 Y128.359 E.02118
; LINE_WIDTH: 0.973955
G1 F2026.766
G1 X119.718 Y128.769 E.17648
G1 X119.716 Y128.761 F30000
; LINE_WIDTH: 0.839619
G1 F2387.97
G1 X121.646 Y128.075 E.25163
G1 X121.643 Y128.068 F30000
; LINE_WIDTH: 0.666681
G1 F3000
G1 X119.714 Y128.755 E.19389
G1 X123.211 Y127.626 F30000
; LINE_WIDTH: 0.75616
G1 F2685.288
G1 X123.322 Y127.855 E.02783
; LINE_WIDTH: 0.71539
G1 F2859.188
G2 X123.449 Y128.113 I4.861 J-2.224 E.02953
; LINE_WIDTH: 0.684775
G1 F3000
G2 X124.351 Y129.457 I6.222 J-3.201 E.15833
; LINE_WIDTH: 0.731963
G1 F2785.85
G1 X124.49 Y129.616 E.0223
; LINE_WIDTH: 0.770838
G1 F2627.749
G2 X124.73 Y129.848 I.735 J-.518 E.03745
; LINE_WIDTH: 0.742863
G1 F2739.633
G1 X124.942 Y129.989 E.02727
; LINE_WIDTH: 0.70638
G1 F2900.703
G2 X125.182 Y130.147 I3.057 J-4.37 E.02905
; LINE_WIDTH: 0.685308
G1 F3000
G2 X126.61 Y130.834 I3.72 J-5.912 E.15519
; LINE_WIDTH: 0.721518
G1 F2831.626
G1 X126.643 Y130.846 E.00356
; LINE_WIDTH: 0.740434
G1 F2749.799
G1 X126.806 Y130.899 E.01835
; LINE_WIDTH: 0.770121
G1 F2630.503
G2 X127.171 Y130.974 I.431 J-1.173 E.04169
; LINE_WIDTH: 0.730827
G1 F2790.758
G1 X127.425 Y130.988 E.02675
; LINE_WIDTH: 0.683053
G1 F3000
G2 X128.789 Y130.947 I.501 J-6.021 E.13306
; LINE_WIDTH: 0.692131
G1 F2968.873
G1 X129.04 Y130.907 E.02514
; LINE_WIDTH: 0.719518
G1 F2840.561
G2 X129.325 Y130.861 I-.721 J-5.309 E.02989
; LINE_WIDTH: 0.749556
G1 F2712.005
G1 X129.455 Y130.833 E.01431
; LINE_WIDTH: 0.769085
G1 F2634.49
G2 X129.809 Y130.704 I-.125 J-.895 E.04226
; LINE_WIDTH: 0.736016
G1 F2768.486
G1 X129.84 Y130.688 E.00373
; LINE_WIDTH: 0.720047
G1 F2838.192
G1 X130.066 Y130.572 E.0263
; LINE_WIDTH: 0.681719
G1 F3000
G2 X131.219 Y129.842 I-2.586 J-5.358 E.13276
; LINE_WIDTH: 0.705091
G1 F2906.74
G1 X131.501 Y129.609 E.03689
; LINE_WIDTH: 0.747483
G1 F2720.504
G1 X131.783 Y129.376 E.03942
; LINE_WIDTH: 0.750517
G1 F2708.087
G1 X131.857 Y129.282 E.013
; LINE_WIDTH: 0.714194
G1 F2864.632
G1 X131.932 Y129.188 E.01229
; LINE_WIDTH: 0.664067
G1 F3000
G1 X132.006 Y129.094 E.01131
G1 X132.4 Y128.307 E.08298
G1 X132.991 Y130.446 F30000
; LINE_WIDTH: 1.07668
G1 F1816.64
G2 X133.398 Y130.808 I7.594 J-8.111 E.0879
; LINE_WIDTH: 1.04725
G1 F1872.259
G1 X133.504 Y130.903 E.02231
; LINE_WIDTH: 0.998379
G1 F1972.521
G1 X133.61 Y130.998 E.02118
; LINE_WIDTH: 0.968691
G1 F2038.85
G1 X134.539 Y131.788 E.17543
G1 X134.534 Y131.794 F30000
; LINE_WIDTH: 0.821309
G1 F2447.42
G1 X132.974 Y130.465 E.24552
G1 X132.969 Y130.471 F30000
; LINE_WIDTH: 0.650149
G1 F3000
G1 X134.529 Y131.799 E.18837
; WIPE_START
G1 F24000
G1 X133.006 Y130.503 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X135.231 Y127.496 Z5.2 F30000
G1 Z4.8
G1 E3 F1800
; LINE_WIDTH: 1.03409
G1 F1898.229
G1 X135.146 Y127.479 E.01335
; LINE_WIDTH: 1.07145
G1 F1826.283
G3 X134.547 Y127.349 I2.36 J-12.281 E.0985
G1 X134.542 Y127.373 F30000
; LINE_WIDTH: 0.825302
G1 F2434.204
G1 X136.554 Y127.756 E.24682
G1 X136.554 Y127.757 F30000
; LINE_WIDTH: 0.650146
G1 F3000
G1 X134.539 Y127.388 E.18837
G1 X135.231 Y127.496 F30000
; LINE_WIDTH: 0.996485
G1 F1976.622
G1 X136.547 Y127.788 E.20013
; WIPE_START
G1 F24000
G1 X135.231 Y127.496 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X135.133 Y123.641 Z5.2 F30000
G1 Z4.8
M73 P76 R2
G1 E3 F1800
; LINE_WIDTH: 0.968692
G1 F2038.849
G1 X136.282 Y123.231 E.17544
G1 X136.284 Y123.239 F30000
; LINE_WIDTH: 0.821312
G1 F2447.41
G1 X134.354 Y123.925 E.24552
G1 X134.357 Y123.932 F30000
; LINE_WIDTH: 0.65016
G1 F3000
G1 X136.286 Y123.245 E.18838
G1 X135.133 Y123.641 F30000
; LINE_WIDTH: 0.998385
G1 F1972.507
G1 X134.998 Y123.685 E.02118
; LINE_WIDTH: 1.04725
G1 F1872.249
G1 X134.863 Y123.729 E.02231
; LINE_WIDTH: 1.07667
G1 F1816.655
G3 X134.346 Y123.9 I-3.737 J-10.44 E.08789
G1 X132.255 Y123.616 F30000
; LINE_WIDTH: 0.662034
G1 F3000
G1 X132.099 Y123.113 E.0495
; LINE_WIDTH: 0.636599
G1 X131.99 Y122.923 E.01963
; LINE_WIDTH: 0.634306
G1 X131.835 Y122.749 E.02087
; LINE_WIDTH: 0.678755
G1 X131.68 Y122.574 E.02256
; LINE_WIDTH: 0.723203
G1 F2824.141
G1 X131.525 Y122.4 E.02425
; LINE_WIDTH: 0.767793
G1 F2639.482
G2 X131.213 Y122.112 I-1.017 J.788 E.04737
; LINE_WIDTH: 0.732189
G1 F2784.875
G1 X131 Y121.973 E.02681
; LINE_WIDTH: 0.683262
G1 F3000
G2 X129.799 Y121.325 I-3.46 J4.976 E.13311
; LINE_WIDTH: 0.691436
G1 F2972.284
G1 X129.562 Y121.234 E.02511
; LINE_WIDTH: 0.71831
G1 F2845.986
G2 X129.291 Y121.131 I-2.032 J4.949 E.02982
; LINE_WIDTH: 0.748433
G1 F2716.601
G1 X129.161 Y121.089 E.0148
; LINE_WIDTH: 0.769614
G1 F2632.45
G2 X128.795 Y121.023 I-.338 J.826 E.04176
; LINE_WIDTH: 0.737491
G1 F2762.216
G1 X128.76 Y121.02 E.00374
; LINE_WIDTH: 0.721249
G1 F2832.825
G1 X128.506 Y121.008 E.02635
; LINE_WIDTH: 0.681836
G1 F3000
G2 X127.143 Y121.062 I-.448 J5.913 E.13278
; LINE_WIDTH: 0.697812
G1 F2941.313
G1 X126.892 Y121.104 E.02538
; LINE_WIDTH: 0.729
G1 F2798.686
G2 X126.606 Y121.153 I.759 J5.313 E.03041
; LINE_WIDTH: 0.762907
G1 F2658.528
G2 X126.128 Y121.327 I.17 J1.208 E.05649
; LINE_WIDTH: 0.725492
G1 F2814.033
G1 X126.097 Y121.342 E.0036
; LINE_WIDTH: 0.685947
G1 F2999.47
G2 X124.727 Y122.201 I2.805 J5.999 E.15858
; LINE_WIDTH: 0.705429
G1 F2905.156
G1 X124.532 Y122.365 E.02571
; LINE_WIDTH: 0.740947
G1 F2747.648
G2 X124.309 Y122.552 I3.355 J4.206 E.03107
; LINE_WIDTH: 0.757936
G1 F2678.193
G1 X124.225 Y122.63 E.01258
G1 X123.998 Y122.955 E.04335
; LINE_WIDTH: 0.685325
G1 F3000
G2 X123.237 Y124.42 I5.849 J3.969 E.1617
; LINE_WIDTH: 0.714295
G1 F2864.172
G1 X123.152 Y124.66 E.02609
; LINE_WIDTH: 0.754166
G1 F2693.3
G2 X123.055 Y124.935 I5.041 J1.932 E.03181
; LINE_WIDTH: 0.781689
G1 F2586.771
G1 X123.045 Y124.969 E.00397
; LINE_WIDTH: 0.766359
G1 F2645.042
G1 X123.026 Y125.206 E.02634
; LINE_WIDTH: 0.724193
G1 F2819.76
G2 X123.006 Y125.476 I5.004 J.513 E.02819
; LINE_WIDTH: 0.68432
G1 F3000
G2 X123.098 Y127.091 I6.892 J.416 E.15816
; LINE_WIDTH: 0.724133
G1 F2820.023
G1 X123.145 Y127.338 E.02615
; LINE_WIDTH: 0.766922
G1 F2642.858
G1 X123.211 Y127.626 E.03274
G1 X123.529 Y130.969 F30000
; LINE_WIDTH: 0.66669
G1 F3000
G1 X122.201 Y132.529 E.1939
G1 X122.206 Y132.534 F30000
; LINE_WIDTH: 0.839629
G1 F2387.939
G1 X123.535 Y130.974 E.25163
G1 X123.554 Y130.991 F30000
; LINE_WIDTH: 1.08005
G1 F1810.49
G2 X123.192 Y131.398 I8.11 J7.593 E.08819
; LINE_WIDTH: 1.04725
G1 F1872.259
G1 X123.097 Y131.504 E.02231
; LINE_WIDTH: 0.998379
G1 F1972.521
G1 X123.002 Y131.61 E.02118
; LINE_WIDTH: 0.973944
G1 F2026.791
G1 X122.212 Y132.539 E.17648
; WIPE_START
G1 F24000
G1 X123.002 Y131.61 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X126.504 Y133.231 Z5.2 F30000
G1 Z4.8
G1 E3 F1800
; LINE_WIDTH: 1.03409
G1 F1898.229
G1 X126.521 Y133.146 E.01335
; LINE_WIDTH: 1.06158
G1 F1844.759
G1 X126.537 Y133.061 E.01373
; LINE_WIDTH: 1.07913
G1 F1812.169
G1 X126.651 Y132.547 E.08529
G1 X126.627 Y132.542 F30000
; LINE_WIDTH: 0.840396
G1 F2385.512
G1 X126.244 Y134.554 E.25186
G1 X126.243 Y134.554 F30000
; LINE_WIDTH: 0.666654
G1 F3000
G1 X126.612 Y132.539 E.19388
G1 X126.504 Y133.231 F30000
; LINE_WIDTH: 1.02035
G1 F1926.146
G1 X126.212 Y134.547 E.20537
; WIPE_START
G1 F24000
G1 X126.504 Y133.231 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X130.359 Y133.133 Z5.2 F30000
G1 Z4.8
G1 E3 F1800
; LINE_WIDTH: 0.968701
G1 F2038.828
G1 X130.769 Y134.282 E.17544
G1 X130.761 Y134.284 F30000
; LINE_WIDTH: 0.821313
G1 F2447.407
G1 X130.075 Y132.354 E.24552
G1 X130.068 Y132.357 F30000
; LINE_WIDTH: 0.65016
G1 F3000
G1 X130.755 Y134.286 E.18838
G1 X130.359 Y133.133 F30000
; LINE_WIDTH: 0.998388
G1 F1972.501
G1 X130.315 Y132.998 E.02118
; LINE_WIDTH: 1.04725
G1 F1872.26
G1 X130.271 Y132.863 E.02231
; LINE_WIDTH: 1.07667
G1 F1816.654
G3 X130.1 Y132.346 I10.474 J-3.748 E.0879
G1 X132.182 Y125.737 F30000
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.830901
G1 F2415.912
G3 X132.185 Y127.372 I-314.677 J1.422 E.19851
G1 X132.67 Y127.614 E.06583
G1 X132.932 Y127.026 E.07816
G2 X132.92 Y125.699 I-285.295 J1.966 E.16119
; LINE_WIDTH: 0.812352
G1 F2477.594
G1 X132.878 Y125.153 E.06482
; LINE_WIDTH: 0.774235
G1 F2614.781
G2 X132.791 Y124.371 I-3.59 J.004 E.08849
G1 X132.702 Y124.22 E.01962
G1 X132.153 Y124.391 E.06443
G1 X132.153 Y124.642 E.02826
; LINE_WIDTH: 0.784055
G1 F2578.007
G1 X132.166 Y125.13 E.05547
; LINE_WIDTH: 0.798203
G1 F2526.803
G1 X132.178 Y125.617 E.05659
G1 X132.471 Y121.031 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 0.650145
G1 F3000
G1 X133.8 Y119.47 E.18848
G1 X133.794 Y119.465 F30000
; LINE_WIDTH: 0.821317
G1 F2447.395
G1 X132.465 Y121.026 E.24568
G1 X132.446 Y121.009 F30000
; LINE_WIDTH: 1.07668
G1 F1816.636
G2 X132.808 Y120.602 I-8.132 J-7.612 E.0879
; LINE_WIDTH: 1.04725
G1 F1872.258
G1 X132.903 Y120.496 E.02231
; LINE_WIDTH: 0.99838
G1 F1972.518
G1 X132.998 Y120.39 E.02118
; LINE_WIDTH: 0.968699
G1 F2038.832
G1 X133.789 Y119.46 E.17563
; WIPE_START
G1 F24000
G1 X132.998 Y120.39 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X129.523 Y118.643 Z5.2 F30000
G1 Z4.8
G1 E3 F1800
; LINE_WIDTH: 0.998378
G1 F1972.521
G1 X129.494 Y118.782 E.02118
; LINE_WIDTH: 1.04725
G1 F1872.25
G1 X129.465 Y118.921 E.02232
; LINE_WIDTH: 1.07667
G1 F1816.654
G3 X129.355 Y119.454 I-10.942 J-1.99 E.08788
G1 X129.523 Y118.643 F30000
; LINE_WIDTH: 0.967153
G1 F2042.408
G1 X129.744 Y117.442 E.17532
; WIPE_START
G1 F24000
G1 X129.523 Y118.643 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X125.641 Y118.867 Z5.2 F30000
G1 Z4.8
G1 E3 F1800
; LINE_WIDTH: 0.998377
G1 F1972.524
G1 X125.685 Y119.002 E.02118
; LINE_WIDTH: 1.04725
G1 F1872.249
G1 X125.729 Y119.137 E.02232
; LINE_WIDTH: 1.08004
G1 F1810.495
G3 X125.9 Y119.654 I-10.465 J3.746 E.08819
G1 X125.925 Y119.646 F30000
; LINE_WIDTH: 0.83963
G1 F2387.934
G1 X125.239 Y117.716 E.25164
G1 X125.245 Y117.714 F30000
; LINE_WIDTH: 0.666679
G1 F3000
G1 X125.932 Y119.643 E.19389
G1 X125.641 Y118.867 F30000
; LINE_WIDTH: 0.973942
G1 F2026.796
G1 X125.231 Y117.718 E.17648
; WIPE_START
G1 F24000
G1 X125.641 Y118.867 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X122.39 Y121.002 Z5.2 F30000
G1 Z4.8
G1 E3 F1800
; LINE_WIDTH: 0.973946
G1 F2026.786
G1 X121.461 Y120.212 E.17648
G1 X121.466 Y120.206 F30000
; LINE_WIDTH: 0.839644
G1 F2387.892
G1 X123.026 Y121.535 E.25164
G1 X123.031 Y121.529 F30000
; LINE_WIDTH: 0.666674
G1 F3000
G1 X121.471 Y120.201 E.19389
G1 X122.39 Y121.002 F30000
; LINE_WIDTH: 0.998378
G1 F1972.521
G1 X122.496 Y121.097 E.02118
; LINE_WIDTH: 1.04725
G1 F1872.261
G1 X122.602 Y121.192 E.02231
; LINE_WIDTH: 1.08005
G1 F1810.489
G3 X123.009 Y121.554 I-7.184 J8.469 E.08819
G1 X121.461 Y124.612 F30000
; LINE_WIDTH: 0.666659
G1 F3000
G1 X119.446 Y124.243 E.19388
G1 X119.446 Y124.244 F30000
; LINE_WIDTH: 0.840395
G1 F2385.515
G1 X121.458 Y124.627 E.25186
G1 X121.453 Y124.651 F30000
; LINE_WIDTH: 1.07912
G1 F1812.172
G1 X120.939 Y124.537 E.08529
; LINE_WIDTH: 1.06158
G1 F1844.764
G1 X120.854 Y124.521 E.01373
; LINE_WIDTH: 1.03409
G1 F1898.239
G1 X120.769 Y124.504 E.01335
; LINE_WIDTH: 1.02035
G1 F1926.153
G1 X119.453 Y124.212 E.20537
; CHANGE_LAYER
; Z_HEIGHT: 5.2
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X120.769 Y124.504 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 13/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L13
M991 S0 P12 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z5.2 I.151 J1.208 P1  F30000
G1 X131.344 Y123.183 Z5.2
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2451.784
G1 X131.444 Y123.276 E.01638
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X127.736 Y121.662 I-2.776 J-3.342 E1.96109
G3 X130.78 Y122.66 I.236 J4.425 E.39219
G1 X131.256 Y123.101 E.07765
G1 X130.709 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X130.71 Y123.596 E.0001
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X127.78 Y122.396 I-2.306 J-2.777 E1.62931
G1 X128.17 Y122.393 E.04657
G3 X130.312 Y123.223 I-.217 J3.743 E.27931
G1 X130.622 Y123.514 E.05089
M204 S10000
; WIPE_START
G1 F24000
G1 X130.71 Y123.596 E-.17217
G1 X130.71 Y125.475 E-2.67783
; WIPE_END
G1 E-.15 F1800
G1 X123.478 Y127.917 Z5.6 F30000
G1 X122.576 Y128.221 Z5.6
G1 Z5.2
G1 E3 F1800
; FEATURE: Inner wall
G1 F2451.784
G1 X122.07 Y128.363 E.0629
G1 X121.931 Y127.979 E.04893
G1 X122.505 Y127.721 E.07525
G3 X122.292 Y125.237 I18.215 J-2.811 E.29852
G1 X121.683 Y125.082 E.07519
G1 X121.755 Y124.679 E.04894
G1 X122.38 Y124.743 E.07524
G3 X123.438 Y122.485 I17.184 J6.675 E.29852
G1 X122.988 Y122.046 E.07519
G1 X123.252 Y121.733 E.04894
G1 X123.762 Y122.101 E.07524
G3 X125.807 Y120.675 I11.543 J14.372 E.29852
G1 X125.637 Y120.07 E.07519
G1 X126.021 Y119.931 E.04893
G1 X126.279 Y120.505 E.07524
G3 X128.763 Y120.292 I2.811 J18.215 E.29852
G1 X128.918 Y119.683 E.07519
G1 X129.321 Y119.755 E.04894
G1 X129.257 Y120.38 E.07524
G3 X131.515 Y121.438 I-6.675 J17.183 E.29852
G1 X131.954 Y120.988 E.07519
G1 X132.267 Y121.252 E.04894
G1 X131.899 Y121.762 E.07524
G3 X133.325 Y123.807 I-14.372 J11.543 E.29852
G1 X133.93 Y123.637 E.07519
G1 X134.069 Y124.021 E.04893
G1 X133.495 Y124.279 E.07525
G3 X133.708 Y126.763 I-18.215 J2.811 E.29852
G1 X134.317 Y126.918 E.07519
G1 X134.245 Y127.321 E.04894
G1 X133.62 Y127.257 E.07524
G3 X132.562 Y129.515 I-17.183 J-6.675 E.29852
G1 X133.012 Y129.954 E.07519
G1 X132.748 Y130.267 E.04894
G1 X132.238 Y129.899 E.07524
G3 X130.193 Y131.325 I-11.544 J-14.372 E.29852
G1 X130.363 Y131.93 E.07519
G1 X129.979 Y132.069 E.04893
G1 X129.721 Y131.495 E.07525
G3 X127.237 Y131.708 I-2.811 J-18.215 E.29852
G1 X127.082 Y132.317 E.07519
G1 X126.679 Y132.245 E.04894
G1 X126.743 Y131.62 E.07524
G3 X124.485 Y130.562 I6.675 J-17.183 E.29852
G1 X124.046 Y131.012 E.07519
G1 X123.733 Y130.748 E.04894
G1 X124.101 Y130.238 E.07524
G3 X122.684 Y128.208 I14.372 J-11.544 E.29645
G1 X122.35 Y129.047 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X122.283 Y129.066 E.00829
G3 X119.569 Y129.424 I-2.337 J-7.252 E.32932
G1 X119.508 Y129.274 E.01936
G1 X119.444 Y129.096 E.02263
G3 X119.331 Y128.765 I3.777 J-1.47 E.04186
G3 X121.708 Y127.274 I5.222 J5.684 E.33766
G3 X121.583 Y125.814 I12.761 J-1.828 E.17541
G1 X121.516 Y125.797 E.00829
G3 X118.987 Y124.75 I1.518 J-7.245 E.32943
G1 X119.009 Y124.588 E.01956
M73 P77 R2
G3 X119.11 Y124.06 I6.093 J.89 E.0643
G3 X121.914 Y123.957 I1.68 J7.534 E.33766
G3 X122.536 Y122.631 I11.968 J4.799 E.17541
G1 X122.486 Y122.582 E.00829
G3 X120.82 Y120.411 I5.112 J-5.65 E.32932
G1 X120.919 Y120.283 E.01936
G1 X121.04 Y120.138 E.02263
G3 X121.271 Y119.875 I3.161 J2.535 E.04186
G3 X123.751 Y121.188 I-2.312 J7.364 E.33766
G3 X124.953 Y120.35 I7.965 J10.139 E.17541
G1 X124.934 Y120.283 E.00829
G3 X124.576 Y117.569 I7.252 J-2.337 E.32932
G1 X124.726 Y117.508 E.01936
G1 X124.904 Y117.444 E.02263
G3 X125.235 Y117.331 I1.47 J3.776 E.04186
G3 X126.726 Y119.708 I-5.684 J5.222 E.33766
G3 X128.186 Y119.583 I1.828 J12.761 E.17541
G1 X128.203 Y119.516 E.00829
G3 X129.25 Y116.987 I7.245 J1.518 E.32944
G1 X129.411 Y117.009 E.01936
G3 X129.94 Y117.11 I-.893 J6.113 E.06449
G3 X130.043 Y119.914 I-7.534 J1.68 E.33766
G3 X131.369 Y120.536 I-4.798 J11.967 E.17541
G1 X131.418 Y120.486 E.00829
G3 X133.589 Y118.82 I5.65 J5.112 E.32932
G1 X133.717 Y118.919 E.01936
G1 X133.862 Y119.04 E.02262
G3 X134.125 Y119.271 I-2.535 J3.161 E.04186
G3 X132.812 Y121.751 I-7.364 J-2.312 E.33766
G3 X133.65 Y122.953 I-10.139 J7.965 E.17541
G1 X133.717 Y122.934 E.00829
G3 X136.431 Y122.576 I2.337 J7.252 E.32932
G1 X136.492 Y122.726 E.01936
G1 X136.556 Y122.903 E.02258
G3 X136.669 Y123.235 I-3.781 J1.472 E.04191
G3 X134.292 Y124.726 I-5.222 J-5.684 E.33766
G3 X134.417 Y126.186 I-12.761 J1.828 E.17541
G1 X134.484 Y126.203 E.00829
G3 X137.013 Y127.25 I-1.518 J7.245 E.32943
G1 X136.991 Y127.412 E.01956
G3 X136.89 Y127.94 I-6.093 J-.89 E.0643
G3 X134.086 Y128.043 I-1.68 J-7.534 E.33766
G3 X133.464 Y129.369 I-11.967 J-4.798 E.17541
G1 X133.514 Y129.418 E.00829
G3 X135.18 Y131.589 I-5.112 J5.65 E.32932
G1 X135.081 Y131.717 E.01936
G1 X134.96 Y131.862 E.02262
G3 X134.729 Y132.125 I-3.161 J-2.535 E.04186
G3 X132.249 Y130.812 I2.312 J-7.364 E.33766
G3 X131.047 Y131.65 I-7.965 J-10.139 E.17541
G1 X131.066 Y131.717 E.00829
G3 X131.424 Y134.431 I-7.252 J2.337 E.32932
G1 X131.274 Y134.492 E.01936
G1 X131.097 Y134.556 E.02258
G3 X130.765 Y134.669 I-1.471 J-3.78 E.0419
G3 X129.274 Y132.292 I5.685 J-5.222 E.33766
G3 X127.814 Y132.417 I-1.828 J-12.761 E.17541
G1 X127.797 Y132.484 E.00829
G3 X126.75 Y135.013 I-7.245 J-1.518 E.32943
G1 X126.588 Y134.991 E.01956
G3 X126.06 Y134.89 I.89 J-6.094 E.0643
G3 X125.957 Y132.086 I7.534 J-1.68 E.33766
G3 X124.631 Y131.464 I4.798 J-11.967 E.17541
G1 X124.582 Y131.514 E.00829
G3 X122.411 Y133.18 I-5.65 J-5.112 E.32932
G1 X122.283 Y133.081 E.01936
G1 X122.138 Y132.96 E.02263
G3 X121.875 Y132.729 I2.535 J-3.161 E.04186
G3 X123.188 Y130.249 I7.364 J2.312 E.33766
G3 X122.413 Y129.149 I10.139 J-7.965 E.16106
M204 S10000
; WIPE_START
G1 F24000
G1 X122.283 Y129.066 E-.22005
G1 X121.714 Y129.226 E-.84316
G1 X121.03 Y129.363 E-.99394
G1 X120.476 Y129.418 E-.79286
; WIPE_END
G1 E-.15 F1800
G1 X121.656 Y128.297 Z5.6 F30000
G1 Z5.2
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 1.04418
G1 F1878.251
G1 X121.296 Y128.427 E.05975
; LINE_WIDTH: 0.997143
G1 F1975.196
G1 X120.936 Y128.556 E.05682
; LINE_WIDTH: 0.973623
G1 F2027.524
G1 X119.798 Y128.997 E.17655
G1 X119.796 Y128.991 F30000
; LINE_WIDTH: 0.839323
G1 F2388.909
G1 X121.647 Y128.273 E.24382
G1 X121.645 Y128.266 F30000
; LINE_WIDTH: 0.666372
G1 F3000
G1 X119.793 Y128.984 E.18785
G1 X123.236 Y127.724 F30000
; LINE_WIDTH: 0.788736
G1 F2560.836
G1 X123.21 Y127.626 E.01163
; LINE_WIDTH: 0.753056
G1 F2697.779
G3 X123.152 Y127.34 I5.26 J-1.22 E.03174
; LINE_WIDTH: 0.713533
G1 F2867.648
G1 X123.102 Y127.09 E.02606
; LINE_WIDTH: 0.682592
G1 F3000
G3 X122.991 Y125.73 I6.566 J-1.219 E.13297
; LINE_WIDTH: 0.717041
G1 F2851.71
G1 X122.992 Y125.475 E.02617
; LINE_WIDTH: 0.732356
G1 F2784.155
G1 X122.994 Y125.44 E.00368
; LINE_WIDTH: 0.773664
G1 F2616.951
G3 X123.063 Y124.937 I1.151 J-.098 E.05745
; LINE_WIDTH: 0.739952
G1 F2751.825
G3 X123.157 Y124.662 I5.132 J1.607 E.03102
; LINE_WIDTH: 0.704776
G1 F2908.219
G1 X123.241 Y124.421 E.02568
; LINE_WIDTH: 0.683192
G1 F3000
G3 X123.838 Y123.194 I6.099 J2.207 E.13312
; LINE_WIDTH: 0.727484
G1 F2805.295
G1 X123.967 Y122.975 E.02661
; LINE_WIDTH: 0.745132
G1 F2730.203
G1 X123.986 Y122.945 E.00383
; LINE_WIDTH: 0.78058
G1 F2590.899
G3 X124.22 Y122.647 I.777 J.369 E.04322
; LINE_WIDTH: 0.760648
G1 F2667.427
G1 X124.315 Y122.557 E.01436
; LINE_WIDTH: 0.728099
G1 F2802.612
G3 X124.535 Y122.368 I3.6 J3.977 E.03036
; LINE_WIDTH: 0.697253
G1 F2944.002
G1 X124.729 Y122.203 E.02536
; LINE_WIDTH: 0.678016
G1 F3000
G3 X125.137 Y121.894 I14.381 J18.524 E.04939
G1 X125.28 Y121.799 E.01658
; LINE_WIDTH: 0.691326
G1 F2972.822
G3 X125.867 Y121.45 I3.697 J5.551 E.06746
; LINE_WIDTH: 0.73917
G1 F2755.118
G1 X126.09 Y121.327 E.02711
; LINE_WIDTH: 0.78181
G1 F2586.321
G3 X126.442 Y121.198 I.587 J1.053 E.04269
; LINE_WIDTH: 0.750772
G1 F2707.045
G1 X126.608 Y121.159 E.01846
; LINE_WIDTH: 0.730699
G1 F2791.311
G1 X126.642 Y121.152 E.00366
; LINE_WIDTH: 0.703337
G1 F2914.997
G1 X127.143 Y121.064 E.0512
; LINE_WIDTH: 0.680233
G1 F3000
G3 X128.219 Y120.988 I1.016 J6.698 E.10463
; LINE_WIDTH: 0.712536
G1 F2872.212
G3 X128.507 Y120.995 I.012 J5.337 E.02938
; LINE_WIDTH: 0.752104
G1 F2701.634
G1 X128.762 Y121.002 E.02766
; LINE_WIDTH: 0.782791
G1 F2582.679
G3 X129.09 Y121.074 I-.019 J.867 E.03839
; LINE_WIDTH: 0.741558
G1 F2745.087
G1 X129.29 Y121.137 E.02245
; LINE_WIDTH: 0.687061
G1 F2993.91
G3 X130.764 Y121.809 I-2.409 J7.241 E.15899
; LINE_WIDTH: 0.722439
G1 F2827.529
G3 X131.009 Y121.961 I-2.702 J4.62 E.0299
; LINE_WIDTH: 0.766305
G1 F2645.253
G1 X131.225 Y122.096 E.02827
; LINE_WIDTH: 0.777291
G1 F2603.224
G1 X131.446 Y122.323 E.03576
; LINE_WIDTH: 0.727754
G1 F2804.115
G1 X131.627 Y122.523 E.02823
; LINE_WIDTH: 0.680918
G1 F3000
G1 X131.809 Y122.723 E.02617
; LINE_WIDTH: 0.634083
G1 X131.99 Y122.924 E.02411
; LINE_WIDTH: 0.615563
G3 X132.066 Y123.046 I-.235 J.23 E.01257
; LINE_WIDTH: 0.648171
G1 X132.099 Y123.116 E.00707
; LINE_WIDTH: 0.668395
G1 X132.244 Y123.563 E.04464
G1 X134.193 Y123.182 F30000
; LINE_WIDTH: 1.06007
G1 F1847.617
G1 X134.806 Y123.536 E.11243
G1 X134.935 Y123.49 E.02177
; LINE_WIDTH: 0.997137
G1 F1975.209
G1 X135.064 Y123.444 E.02036
; LINE_WIDTH: 0.968362
G1 F2039.611
G1 X136.202 Y123.003 E.1755
G1 X136.204 Y123.009 F30000
; LINE_WIDTH: 0.821011
G1 F2448.412
G1 X134.353 Y123.727 E.23789
G1 X134.355 Y123.734 F30000
; LINE_WIDTH: 0.649886
G1 F3000
G1 X136.207 Y123.016 E.18252
; WIPE_START
G1 F24000
G1 X134.355 Y123.734 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X132.783 Y121.163 Z5.6 F30000
G1 Z5.2
G1 E3 F1800
; LINE_WIDTH: 1.06009
G1 F1847.586
G1 X132.662 Y120.464 E.11276
G1 X132.751 Y120.359 E.02177
; LINE_WIDTH: 0.997135
G1 F1975.213
G1 X132.839 Y120.254 E.02036
; LINE_WIDTH: 0.968361
G1 F2039.612
G1 X133.604 Y119.303 E.17551
G1 X133.61 Y119.308 F30000
; LINE_WIDTH: 0.821003
G1 F2448.438
G1 X132.365 Y120.855 E.23789
G1 X132.371 Y120.86 F30000
; LINE_WIDTH: 0.64987
G1 F3000
G1 X133.615 Y119.312 E.18252
; WIPE_START
G1 F24000
G1 X132.371 Y120.86 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X129.724 Y119.42 Z5.6 F30000
G1 Z5.2
G1 E3 F1800
; LINE_WIDTH: 1.06009
G1 F1847.575
G1 X129.27 Y118.874 E.11276
G1 X129.294 Y118.739 E.02177
; LINE_WIDTH: 0.997132
G1 F1975.22
G1 X129.318 Y118.604 E.02036
; LINE_WIDTH: 0.966829
G1 F2043.161
G1 X129.505 Y117.398 E.17519
; WIPE_START
G1 F24000
G1 X129.318 Y118.604 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X125.444 Y118.936 Z5.6 F30000
G1 Z5.2
G1 E3 F1800
; LINE_WIDTH: 0.973616
G1 F2027.54
G1 X125.003 Y117.798 E.17655
G1 X125.009 Y117.796 F30000
; LINE_WIDTH: 0.839324
G1 F2388.906
G1 X125.727 Y119.647 E.24382
G1 X125.734 Y119.645 F30000
; LINE_WIDTH: 0.666389
G1 F3000
G1 X125.016 Y117.793 E.18786
G1 X125.444 Y118.936 F30000
; LINE_WIDTH: 0.997138
G1 F1975.207
G1 X125.573 Y119.296 E.05682
; LINE_WIDTH: 1.04418
G1 F1878.251
G1 X125.703 Y119.656 E.05975
G1 X122.86 Y121.629 F30000
; LINE_WIDTH: 0.666378
G1 F3000
G1 X121.312 Y120.385 E.18786
G1 X121.308 Y120.39 F30000
; LINE_WIDTH: 0.839332
G1 F2388.881
G1 X122.855 Y121.635 E.24382
G1 X122.838 Y121.654 F30000
; LINE_WIDTH: 1.04418
G1 F1878.254
G1 X122.546 Y121.408 E.05975
; LINE_WIDTH: 0.997136
G1 F1975.211
G1 X122.254 Y121.161 E.05682
; LINE_WIDTH: 0.973614
G1 F2027.546
G1 X121.303 Y120.396 E.17654
; WIPE_START
G1 F24000
G1 X122.254 Y121.161 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.236 Y127.724 Z5.6 F30000
G1 Z5.2
G1 E3 F1800
; LINE_WIDTH: 0.781931
G1 F2585.871
G1 X123.329 Y127.906 E.02321
; LINE_WIDTH: 0.739637
G1 F2753.153
G2 X123.439 Y128.119 I3.996 J-1.931 E.02546
; LINE_WIDTH: 0.68679
G1 F2995.259
G2 X124.354 Y129.453 I6.501 J-3.478 E.15885
; LINE_WIDTH: 0.723558
G1 F2822.569
G1 X124.524 Y129.643 E.02649
; LINE_WIDTH: 0.767457
G1 F2640.782
G2 X124.72 Y129.861 I4.122 J-3.51 E.03255
; LINE_WIDTH: 0.795647
G1 F2535.902
G1 X124.735 Y129.877 E.00249
; LINE_WIDTH: 0.777051
G1 F2604.129
G1 X124.941 Y130.008 E.02753
; LINE_WIDTH: 0.731266
G1 F2788.857
G2 X125.176 Y130.156 I2.874 J-4.295 E.02925
; LINE_WIDTH: 0.686522
G1 F2996.598
G2 X126.644 Y130.84 I3.905 J-6.461 E.1588
; LINE_WIDTH: 0.733966
G1 F2777.24
G1 X126.877 Y130.915 E.02589
; LINE_WIDTH: 0.779713
G1 F2594.136
G1 X127.169 Y130.994 E.03414
; LINE_WIDTH: 0.764549
G1 F2652.095
G1 X127.423 Y131.003 E.02819
; LINE_WIDTH: 0.721198
G1 F2833.052
G2 X127.711 Y131.012 I.313 J-5.345 E.02984
; LINE_WIDTH: 0.687187
G1 F2993.284
G2 X129.323 Y130.854 I.069 J-7.636 E.15904
; LINE_WIDTH: 0.742612
G1 F2740.678
G1 X129.524 Y130.809 E.02199
; LINE_WIDTH: 0.78289
G1 F2582.314
G2 X129.848 Y130.705 I-.11 J-.894 E.03891
; LINE_WIDTH: 0.75051
G1 F2708.113
G1 X130.072 Y130.583 E.02759
; LINE_WIDTH: 0.711449
G1 F2877.2
G2 X130.324 Y130.445 I-2.432 J-4.753 E.02932
; LINE_WIDTH: 0.680114
G1 F3000
G2 X131.217 Y129.84 I-3.314 J-5.852 E.10461
; LINE_WIDTH: 0.700796
G1 F2927.04
G1 X131.553 Y129.558 E.04398
; LINE_WIDTH: 0.739491
G1 F2753.766
G1 X131.889 Y129.276 E.04675
G1 X132.018 Y129.107 E.02262
; LINE_WIDTH: 0.693206
G1 F2963.62
G1 X132.402 Y128.298 E.08858
G1 X133.537 Y129.954 F30000
; LINE_WIDTH: 1.06007
G1 F1847.612
G1 X133.536 Y130.662 E.11243
G1 X133.641 Y130.751 E.02177
; LINE_WIDTH: 0.997136
G1 F1975.211
G1 X133.746 Y130.839 E.02036
; LINE_WIDTH: 0.968363
G1 F2039.609
G1 X134.697 Y131.604 E.1755
G1 X134.692 Y131.61 F30000
; LINE_WIDTH: 0.821005
G1 F2448.433
G1 X133.145 Y130.365 E.23789
G1 X133.14 Y130.371 F30000
; LINE_WIDTH: 0.649865
G1 F3000
M73 P78 R2
G1 X134.688 Y131.615 E.18251
; WIPE_START
G1 F24000
G1 X133.14 Y130.371 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X130.818 Y132.193 Z5.6 F30000
G1 Z5.2
G1 E3 F1800
; LINE_WIDTH: 1.06007
G1 F1847.615
G1 X130.464 Y132.806 E.11244
G1 X130.51 Y132.935 E.02176
; LINE_WIDTH: 0.997144
G1 F1975.193
G1 X130.556 Y133.064 E.02036
; LINE_WIDTH: 0.968362
G1 F2039.611
G1 X130.997 Y134.202 E.1755
G1 X130.991 Y134.204 F30000
; LINE_WIDTH: 0.821006
G1 F2448.43
G1 X130.273 Y132.353 E.23789
G1 X130.266 Y132.355 F30000
; LINE_WIDTH: 0.649884
G1 F3000
G1 X130.984 Y134.207 E.18252
; WIPE_START
G1 F24000
G1 X130.266 Y132.355 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.654 Y131.162 Z5.6 F30000
G1 Z5.2
G1 E3 F1800
; LINE_WIDTH: 1.04418
G1 F1878.249
G1 X123.408 Y131.454 E.05975
; LINE_WIDTH: 0.997136
G1 F1975.209
G1 X123.161 Y131.746 E.05682
; LINE_WIDTH: 0.973615
G1 F2027.543
G1 X122.396 Y132.697 E.17655
G1 X122.39 Y132.692 F30000
; LINE_WIDTH: 0.83933
G1 F2388.887
G1 X123.635 Y131.145 E.24382
G1 X123.629 Y131.14 F30000
; LINE_WIDTH: 0.666377
G1 F3000
G1 X122.385 Y132.688 E.18786
; WIPE_START
G1 F24000
G1 X123.629 Y131.14 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X130.038 Y126.996 Z5.6 F30000
G1 X132.179 Y125.611 Z5.6
G1 Z5.2
G1 E3 F1800
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.842978
G1 F2377.376
G3 X132.194 Y127.37 I-71.662 J1.482 E.21704
G1 X132.663 Y127.592 E.06401
G1 X132.963 Y126.885 E.09487
G2 X132.912 Y125.566 I-1309.948 J49.932 E.1628
; LINE_WIDTH: 0.806021
G1 F2499.373
G1 X132.865 Y125.052 E.06061
; LINE_WIDTH: 0.763444
G1 F2656.421
G2 X132.768 Y124.242 I-5.324 J.228 E.09023
G1 X132.71 Y124.152 E.01178
G1 X132.148 Y124.334 E.06528
G1 X132.148 Y124.579 E.02704
; LINE_WIDTH: 0.774558
G1 F2613.554
G1 X132.162 Y125.035 E.05123
; LINE_WIDTH: 0.79029
G1 F2555.188
G1 X132.176 Y125.491 E.0524
G1 X134.773 Y126.656 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 1.06007
G1 F1847.607
G1 X135.126 Y127.27 E.11243
G1 X135.261 Y127.294 E.02177
; LINE_WIDTH: 0.997132
G1 F1975.219
G1 X135.396 Y127.318 E.02036
; LINE_WIDTH: 0.966831
G1 F2043.154
G1 X136.602 Y127.505 E.17519
; CHANGE_LAYER
; Z_HEIGHT: 5.6
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X135.396 Y127.318 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 14/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L14
M991 S0 P13 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z5.6 I.869 J-.852 P1  F30000
G1 X131.344 Y123.183 Z5.6
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2416
G1 X131.444 Y123.276 E.01637
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X128.115 Y121.66 I-2.776 J-3.339 E2.00607
G3 X130.78 Y122.66 I-.136 J4.415 E.3468
G1 X131.256 Y123.101 E.07766
G1 X130.709 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2416
G1 X130.71 Y123.596 E.00011
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X128.12 Y122.394 I-2.307 J-2.775 E1.6697
G3 X130.31 Y123.225 I-.187 J3.794 E.28489
G1 X130.621 Y123.514 E.05085
M204 S10000
; WIPE_START
G1 F24000
G1 X130.71 Y123.596 E-.17234
G1 X130.71 Y125.475 E-2.67766
; WIPE_END
G1 E-.15 F1800
G1 X123.526 Y128.053 Z6 F30000
G1 X122.658 Y128.364 Z6
G1 Z5.6
G1 E3 F1800
; FEATURE: Inner wall
G1 F2416
G1 X122.248 Y128.492 E.05142
G1 X122.101 Y128.104 E.04967
G1 X122.566 Y127.896 E.06097
G3 X122.298 Y125.4 I13.305 J-2.69 E.30072
G1 X121.772 Y125.282 E.0645
G1 X121.839 Y124.872 E.04967
G1 X122.346 Y124.925 E.06099
G3 X123.362 Y122.63 I12.868 J4.323 E.30071
G1 X122.965 Y122.264 E.06449
G1 X123.228 Y121.943 E.04967
G1 X123.641 Y122.242 E.06098
G3 X125.668 Y120.762 I8.982 J10.177 E.30071
G1 X125.508 Y120.248 E.06448
G1 X125.896 Y120.101 E.04967
G1 X126.104 Y120.566 E.06097
G3 X128.6 Y120.298 I2.69 J13.305 E.30072
G1 X128.718 Y119.772 E.0645
G1 X129.128 Y119.839 E.04967
G1 X129.075 Y120.346 E.06098
G3 X131.37 Y121.362 I-4.323 J12.868 E.30071
G1 X131.736 Y120.965 E.06449
G1 X132.057 Y121.228 E.04967
G1 X131.758 Y121.641 E.06098
G3 X133.238 Y123.668 I-10.176 J8.982 E.30072
G1 X133.752 Y123.508 E.06448
G1 X133.899 Y123.896 E.04967
G1 X133.434 Y124.104 E.06097
G3 X133.702 Y126.6 I-13.305 J2.69 E.30072
G1 X134.228 Y126.718 E.06449
G1 X134.161 Y127.128 E.04967
G1 X133.654 Y127.075 E.06097
G3 X132.638 Y129.37 I-12.868 J-4.323 E.30072
G1 X133.035 Y129.736 E.06449
G1 X132.772 Y130.057 E.04967
G1 X132.359 Y129.758 E.06098
G3 X130.332 Y131.238 I-8.982 J-10.176 E.30071
G1 X130.492 Y131.752 E.06448
G1 X130.104 Y131.899 E.04967
G1 X129.896 Y131.434 E.06097
G3 X127.4 Y131.702 I-2.69 J-13.305 E.30072
G1 X127.282 Y132.228 E.06449
G1 X126.872 Y132.161 E.04967
G1 X126.925 Y131.654 E.06097
G3 X124.63 Y130.638 I4.323 J-12.869 E.30072
G1 X124.264 Y131.035 E.06449
G1 X123.943 Y130.772 E.04967
G1 X124.242 Y130.359 E.06098
G3 X122.768 Y128.341 I10.176 J-8.982 E.29942
G1 X122.446 Y129.199 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2416
G1 X122.367 Y129.224 E.00992
G3 X119.662 Y129.649 I-2.404 J-6.481 E.32978
G1 X119.604 Y129.507 E.01832
G3 X119.411 Y129.005 I5.653 J-2.46 E.06438
G3 X121.751 Y127.456 I5.038 J5.069 E.338
G3 X121.59 Y125.994 I9.92 J-1.829 E.17617
G1 X121.51 Y125.976 E.00992
G3 X118.955 Y124.991 I1.158 J-6.813 E.32979
G1 X118.975 Y124.839 E.01831
G3 X119.059 Y124.308 I6.127 J.696 E.06438
G3 X121.86 Y124.137 I1.829 J6.909 E.338
G3 X122.452 Y122.79 I9.506 J3.376 E.17617
G1 X122.391 Y122.734 E.00992
G3 X120.671 Y120.604 I4.41 J-5.322 E.32978
G1 X120.764 Y120.482 E.01832
G3 X121.103 Y120.064 I4.957 J3.666 E.06438
G3 X123.615 Y121.316 I-1.87 J6.898 E.338
G3 X124.801 Y120.446 I6.544 J7.676 E.17617
G1 X124.776 Y120.367 E.00992
G3 X124.351 Y117.662 I6.481 J-2.404 E.32978
G1 X124.493 Y117.604 E.01832
G3 X124.995 Y117.411 I2.461 J5.654 E.06438
G3 X126.544 Y119.751 I-5.069 J5.038 E.338
G3 X128.006 Y119.59 I1.829 J9.92 E.17617
G1 X128.024 Y119.51 E.00992
G3 X128.998 Y116.956 I7.507 J1.4 E.3288
G1 X129.16 Y116.976 E.01945
G3 X129.692 Y117.059 I-.566 J5.408 E.06447
G3 X129.863 Y119.86 I-6.909 J1.829 E.338
G3 X131.21 Y120.452 I-3.376 J9.506 E.17617
G1 X131.266 Y120.391 E.00992
G3 X133.396 Y118.671 I5.322 J4.41 E.32978
G1 X133.518 Y118.764 E.01832
G3 X133.936 Y119.103 I-3.666 J4.958 E.06438
G3 X132.684 Y121.615 I-6.898 J-1.87 E.338
G3 X133.554 Y122.801 I-7.676 J6.544 E.17617
G1 X133.633 Y122.776 E.00992
G3 X136.338 Y122.351 I2.404 J6.481 E.32978
G1 X136.396 Y122.493 E.01832
G3 X136.589 Y122.995 I-5.654 J2.461 E.06438
G3 X134.249 Y124.544 I-5.038 J-5.069 E.338
G3 X134.41 Y126.006 I-9.92 J1.829 E.17617
G1 X134.49 Y126.024 E.00992
G3 X137.045 Y127.009 I-1.158 J6.813 E.32979
G1 X137.025 Y127.161 E.01831
G3 X136.941 Y127.692 I-6.127 J-.696 E.06438
G3 X134.14 Y127.863 I-1.829 J-6.909 E.338
G3 X133.548 Y129.21 I-9.506 J-3.376 E.17617
G1 X133.609 Y129.266 E.00992
G3 X135.329 Y131.396 I-4.41 J5.322 E.32978
G1 X135.236 Y131.518 E.01832
G3 X134.897 Y131.936 I-4.958 J-3.666 E.06438
G3 X132.385 Y130.684 I1.87 J-6.898 E.338
G3 X131.199 Y131.554 I-6.544 J-7.676 E.17617
G1 X131.224 Y131.633 E.00992
G3 X131.649 Y134.338 I-6.481 J2.404 E.32978
G1 X131.507 Y134.396 E.01832
G3 X131.005 Y134.589 I-2.461 J-5.654 E.06438
G3 X129.456 Y132.249 I5.069 J-5.038 E.338
G3 X127.994 Y132.41 I-1.829 J-9.92 E.17617
G1 X127.976 Y132.49 E.00992
G3 X126.991 Y135.045 I-6.813 J-1.158 E.32979
G1 X126.839 Y135.025 E.01831
G3 X126.308 Y134.941 I.696 J-6.125 E.06438
G3 X126.137 Y132.14 I6.909 J-1.829 E.338
G3 X124.79 Y131.548 I3.376 J-9.506 E.17617
G1 X124.734 Y131.609 E.00992
G3 X122.604 Y133.329 I-5.322 J-4.41 E.32978
G1 X122.482 Y133.236 E.01832
G3 X122.064 Y132.897 I3.667 J-4.959 E.06438
G3 X123.316 Y130.385 I6.898 J1.87 E.338
G3 X122.51 Y129.301 I7.676 J-6.544 E.16182
M204 S10000
; WIPE_START
G1 F24000
G1 X122.367 Y129.224 E-.2318
G1 X121.805 Y129.399 E-.83836
G1 X121.126 Y129.556 E-.99367
G1 X120.578 Y129.625 E-.78617
; WIPE_END
G1 E-.15 F1800
G1 X121.831 Y128.429 Z6 F30000
G1 Z5.6
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 1.08545
G2 X121.275 Y128.648 I4.179 J11.443 E.09741
; LINE_WIDTH: 1.04694
G1 F1872.847
G1 X121.142 Y128.7 E.0223
; LINE_WIDTH: 0.998084
G1 F1973.157
G1 X121.01 Y128.752 E.02117
; LINE_WIDTH: 0.973655
G1 F2027.452
G1 X119.885 Y129.224 E.17651
G1 X119.882 Y129.217 F30000
; LINE_WIDTH: 0.839352
G1 F2388.815
G1 X121.822 Y128.403 E.25828
G1 X121.325 Y125.558 F30000
; LINE_WIDTH: 0.993834
G1 F1982.392
M73 P79 R2
G1 X121.198 Y125.353 E.03564
; LINE_WIDTH: 1.03445
G1 F1897.515
G1 X121.071 Y125.149 E.03723
; LINE_WIDTH: 1.07748
G1 F1815.173
G1 X120.944 Y124.944 E.03892
G1 X120.869 Y124.932 E.0122
; LINE_WIDTH: 1.06063
G1 F1846.544
G1 X120.78 Y124.919 E.01435
; LINE_WIDTH: 1.03188
G1 F1902.667
G1 X120.69 Y124.907 E.01393
; LINE_WIDTH: 0.995893
G1 F1977.909
G1 X120.57 Y124.888 E.01803
; LINE_WIDTH: 0.97428
G1 F2026.024
G1 X119.361 Y124.727 E.17663
G1 X119.361 Y124.727 F30000
; LINE_WIDTH: 0.839362
G1 F2388.784
G1 X121.447 Y124.992 E.25827
G1 X122.812 Y121.872 F30000
; LINE_WIDTH: 1.08543
G1 F1800.735
G2 X122.344 Y121.5 I-7.817 J9.336 E.09739
; LINE_WIDTH: 1.04694
G1 F1872.855
G1 X122.233 Y121.411 E.0223
; LINE_WIDTH: 0.99808
G1 F1973.166
G1 X122.122 Y121.322 E.02117
; LINE_WIDTH: 0.97365
G1 F2027.462
G1 X121.15 Y120.584 E.17651
G1 X121.155 Y120.578 F30000
; LINE_WIDTH: 0.839345
G1 F2388.838
G1 X122.829 Y121.851 E.25827
G1 X125.571 Y119.831 F30000
; LINE_WIDTH: 1.08544
G1 F1800.715
G2 X125.352 Y119.275 I-11.457 J4.184 E.09741
; LINE_WIDTH: 1.04694
G1 F1872.847
G1 X125.3 Y119.142 E.0223
; LINE_WIDTH: 0.998088
G1 F1973.149
G1 X125.248 Y119.01 E.02117
; LINE_WIDTH: 0.973661
G1 F2027.437
G1 X124.776 Y117.885 E.17652
G1 X124.783 Y117.882 F30000
; LINE_WIDTH: 0.839344
G1 F2388.841
G1 X125.597 Y119.821 E.25828
G1 X128.442 Y119.325 F30000
; LINE_WIDTH: 1.01418
G1 F1938.95
G1 X128.647 Y119.198 E.03644
; LINE_WIDTH: 1.03448
G1 F1897.46
G1 X128.851 Y119.071 E.03723
; LINE_WIDTH: 1.07507
G1 F1819.59
G1 X129.056 Y118.944 E.03883
; LINE_WIDTH: 1.07182
G1 F1825.605
G2 X129.081 Y118.78 I-3.33 J-.583 E.02664
; LINE_WIDTH: 1.03189
G1 F1902.653
G1 X129.093 Y118.69 E.01393
; LINE_WIDTH: 0.995896
G1 F1977.902
G1 X129.112 Y118.57 E.01804
; LINE_WIDTH: 0.970427
G1 F2034.849
G1 X129.273 Y117.361 E.1759
G1 X129.273 Y117.361 F30000
; LINE_WIDTH: 0.839362
G1 F2388.785
G1 X129.008 Y119.447 E.25831
G1 X132.128 Y120.812 F30000
; LINE_WIDTH: 1.07639
G1 F1817.182
G2 X132.5 Y120.344 I-9.368 J-7.842 E.09651
; LINE_WIDTH: 1.04695
G1 F1872.837
G1 X132.589 Y120.233 E.0223
; LINE_WIDTH: 0.998088
G1 F1973.149
G1 X132.678 Y120.122 E.02117
; LINE_WIDTH: 0.968402
G1 F2039.518
G1 X133.416 Y119.15 E.17558
G1 X133.422 Y119.154 F30000
; LINE_WIDTH: 0.82103
G1 F2416
G1 X132.149 Y120.829 E.25209
G1 X134.169 Y123.571 F30000
; LINE_WIDTH: 1.07639
G1 F1817.182
G2 X134.725 Y123.352 I-4.19 J-11.471 E.09653
; LINE_WIDTH: 1.04695
G1 F1872.844
G1 X134.858 Y123.3 E.0223
; LINE_WIDTH: 0.998085
G1 F1973.155
G1 X134.99 Y123.248 E.02117
; LINE_WIDTH: 0.9684
G1 F2039.524
G1 X136.116 Y122.776 E.17558
G1 X136.119 Y122.783 F30000
; LINE_WIDTH: 0.821036
G1 F2416
G1 X134.179 Y123.597 E.2521
G1 X134.552 Y127.008 F30000
; LINE_WIDTH: 0.821039
G1 F2416
G1 X136.639 Y127.273 E.252
G1 X136.639 Y127.273 F30000
; LINE_WIDTH: 0.970428
G1 F2034.846
G1 X135.43 Y127.112 E.17586
; LINE_WIDTH: 0.995895
G1 F1977.905
G1 X135.31 Y127.093 E.01803
; LINE_WIDTH: 1.03189
G1 F1902.659
G1 X135.22 Y127.081 E.01393
; LINE_WIDTH: 1.07182
G1 F1825.587
G3 X135.056 Y127.056 I.42 J-3.355 E.02665
; LINE_WIDTH: 1.07512
G1 F1819.509
G1 X134.929 Y126.851 E.03883
; LINE_WIDTH: 1.03457
G1 F1897.283
G1 X134.802 Y126.647 E.03724
; LINE_WIDTH: 1.01429
G1 F1938.718
G1 X134.675 Y126.442 E.03644
G1 X132.176 Y125.475 F30000
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.840659
G1 F2384.68
G3 X132.194 Y127.36 I-65.988 J1.568 E.23192
G1 X132.657 Y127.58 E.06304
G1 X132.962 Y126.787 E.10456
G3 X132.904 Y125.454 I46.578 J-2.705 E.16407
; LINE_WIDTH: 0.797421
G1 F2416
G1 X132.85 Y124.997 E.05344
; LINE_WIDTH: 0.750929
G2 X132.705 Y124.126 I-4.257 J.266 E.09588
G1 X132.141 Y124.375 E.0668
; LINE_WIDTH: 0.762892
G1 X132.157 Y124.865 E.05407
; LINE_WIDTH: 0.780157
G1 X132.172 Y125.355 E.05545
G1 X132.29 Y123.547 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 0.636427
G1 F2416
G1 X132.049 Y123.003 E.05343
; LINE_WIDTH: 0.612713
G2 X131.945 Y122.875 I-.724 J.481 E.01412
; LINE_WIDTH: 0.644698
G1 X131.712 Y122.626 E.03105
; LINE_WIDTH: 0.69201
G1 X131.479 Y122.378 E.03368
; LINE_WIDTH: 0.739322
G1 X131.246 Y122.129 E.03631
; LINE_WIDTH: 0.77157
G1 X131.187 Y122.071 E.00919
; LINE_WIDTH: 0.762344
G1 X130.99 Y121.948 E.02561
; LINE_WIDTH: 0.721925
G2 X130.764 Y121.808 I-2.712 J4.119 E.02754
; LINE_WIDTH: 0.683242
G2 X129.288 Y121.148 I-3.455 J5.744 E.15785
; LINE_WIDTH: 0.719553
G1 X129.043 Y121.076 E.02632
; LINE_WIDTH: 0.761081
G1 X128.762 Y121.001 E.03207
; LINE_WIDTH: 0.753585
G1 X128.507 Y120.995 E.02772
; LINE_WIDTH: 0.713778
G2 X128.219 Y120.988 I-.273 J5.338 E.02944
; LINE_WIDTH: 0.683543
G2 X126.612 Y121.171 I-.031 J6.862 E.15796
; LINE_WIDTH: 0.727146
G1 X126.402 Y121.224 E.02265
; LINE_WIDTH: 0.76579
G2 X126.09 Y121.327 I.115 J.874 E.0366
; LINE_WIDTH: 0.74058
G1 X125.867 Y121.45 E.02717
; LINE_WIDTH: 0.691175
G2 X125.23 Y121.83 I3.381 J6.385 E.07324
; LINE_WIDTH: 0.685533
G1 X125.186 Y121.859 E.00518
G2 X124.325 Y122.566 I4.671 J6.562 E.10889
; LINE_WIDTH: 0.735259
G1 X124.199 Y122.69 E.01875
; LINE_WIDTH: 0.76562
G2 X123.967 Y122.974 I.821 J.907 E.04084
; LINE_WIDTH: 0.728831
G1 X123.837 Y123.193 E.02667
; LINE_WIDTH: 0.682388
G2 X123.246 Y124.423 I5.079 J3.198 E.13289
; LINE_WIDTH: 0.701235
G1 X123.088 Y124.906 E.05102
; LINE_WIDTH: 0.727623
G1 X123.078 Y124.939 E.00363
; LINE_WIDTH: 0.74401
G1 X123.042 Y125.072 E.01474
; LINE_WIDTH: 0.764905
G2 X122.993 Y125.44 I.862 J.303 E.04141
; LINE_WIDTH: 0.73376
G1 X122.992 Y125.475 E.0037
; LINE_WIDTH: 0.718314
G1 X122.991 Y125.73 E.02622
; LINE_WIDTH: 0.681004
G2 X123.109 Y127.088 I5.875 J.174 E.13257
; LINE_WIDTH: 0.695314
G1 X123.163 Y127.337 E.02527
; LINE_WIDTH: 0.725187
G2 X123.226 Y127.62 I5.26 J-1.018 E.0302
; LINE_WIDTH: 0.758356
G2 X123.422 Y128.089 I1.227 J-.237 E.05609
; LINE_WIDTH: 0.689274
G2 X123.977 Y128.979 I6.983 J-3.738 E.10322
; LINE_WIDTH: 0.679296
G1 X124.015 Y129.031 E.0063
G2 X124.36 Y129.447 I24.246 J-19.712 E.05228
; LINE_WIDTH: 0.702554
G1 X124.533 Y129.634 E.02558
; LINE_WIDTH: 0.736748
G2 X124.731 Y129.847 I4.033 J-3.557 E.03084
; LINE_WIDTH: 0.753638
G1 X124.814 Y129.928 E.01259
G1 X125.147 Y130.139 E.04296
; LINE_WIDTH: 0.684218
G2 X126.646 Y130.831 I3.65 J-5.943 E.16136
; LINE_WIDTH: 0.711039
G1 X126.89 Y130.904 E.02595
; LINE_WIDTH: 0.749583
G2 X127.169 Y130.987 I1.68 J-5.127 E.03155
; LINE_WIDTH: 0.776404
G1 X127.204 Y130.996 E.00404
; LINE_WIDTH: 0.761783
G1 X127.441 Y131.004 E.02611
; LINE_WIDTH: 0.721071
G2 X127.711 Y131.012 I.29 J-5.014 E.02799
; LINE_WIDTH: 0.683234
G2 X129.32 Y130.844 I.109 J-6.724 E.15785
; LINE_WIDTH: 0.720527
G1 X129.564 Y130.784 E.02603
; LINE_WIDTH: 0.762069
G1 X129.848 Y130.705 E.03244
; LINE_WIDTH: 0.751973
G1 X130.072 Y130.584 E.02765
; LINE_WIDTH: 0.712677
G2 X130.324 Y130.446 I-2.437 J-4.757 E.02938
; LINE_WIDTH: 0.680089
G2 X131.215 Y129.838 I-3.274 J-5.755 E.10457
; LINE_WIDTH: 0.6888
G1 X131.581 Y129.52 E.04764
; LINE_WIDTH: 0.701058
G1 X131.947 Y129.202 E.04861
G1 X132.018 Y129.107 E.01188
G1 X132.406 Y128.29 E.09067
G1 X133.188 Y130.128 F30000
; LINE_WIDTH: 1.07638
G1 F1817.187
G2 X133.656 Y130.5 I7.833 J-9.356 E.09651
; LINE_WIDTH: 1.04694
G1 F1872.852
G1 X133.767 Y130.589 E.0223
; LINE_WIDTH: 0.998083
G1 F1973.161
G1 X133.878 Y130.678 E.02117
; LINE_WIDTH: 0.968401
G1 F2039.52
G1 X134.85 Y131.416 E.17547
G1 X134.845 Y131.422 F30000
; LINE_WIDTH: 0.821037
G1 F2416
G1 X133.171 Y130.149 E.25199
G1 X130.429 Y132.169 F30000
; LINE_WIDTH: 1.07638
G1 F1817.184
G2 X130.648 Y132.725 I11.441 J-4.178 E.09653
; LINE_WIDTH: 1.04695
G1 F1872.844
G1 X130.7 Y132.858 E.0223
; LINE_WIDTH: 0.99809
G1 F1973.146
G1 X130.752 Y132.99 E.02117
; LINE_WIDTH: 0.968402
G1 F2039.518
G1 X131.224 Y134.115 E.17547
G1 X131.217 Y134.118 F30000
; LINE_WIDTH: 0.821032
G1 F2416
G1 X130.403 Y132.178 E.252
G1 X127.558 Y132.675 F30000
; LINE_WIDTH: 0.993954
G1 F1982.132
G1 X127.353 Y132.802 E.03564
; LINE_WIDTH: 1.03453
G1 F1897.356
G1 X127.149 Y132.929 E.03723
; LINE_WIDTH: 1.07752
G1 F1815.111
G1 X126.944 Y133.056 E.03892
G1 X126.932 Y133.131 E.01221
; LINE_WIDTH: 1.06063
G1 F1846.547
G1 X126.919 Y133.22 E.01435
; LINE_WIDTH: 1.03188
G1 F1902.674
G1 X126.907 Y133.31 E.01393
; LINE_WIDTH: 0.995889
G1 F1977.916
G1 X126.888 Y133.43 E.01803
; LINE_WIDTH: 0.97428
G1 F2026.026
G1 X126.727 Y134.639 E.17662
G1 X126.727 Y134.639 F30000
; LINE_WIDTH: 0.839362
G1 F2388.785
G1 X126.992 Y132.552 E.25828
G1 X123.872 Y131.188 F30000
; LINE_WIDTH: 1.08543
G1 F1800.737
G2 X123.5 Y131.656 I9.337 J7.818 E.09739
; LINE_WIDTH: 1.04694
G1 F1872.858
G1 X123.411 Y131.767 E.0223
; LINE_WIDTH: 0.998081
G1 F1973.165
G1 X123.322 Y131.878 E.02117
; LINE_WIDTH: 0.97365
G1 F2027.462
G1 X122.584 Y132.85 E.17651
G1 X122.578 Y132.845 F30000
; LINE_WIDTH: 0.839346
G1 F2388.836
G1 X123.851 Y131.171 E.25827
; CHANGE_LAYER
; Z_HEIGHT: 6
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X122.641 Y132.763 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 15/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L15
M991 S0 P14 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z6 I.901 J.818 P1  F30000
G1 X131.344 Y123.183 Z6
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2451.784
G1 X131.444 Y123.276 E.01637
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X128.087 Y121.66 I-2.779 J-3.338 E2.00355
G3 X130.78 Y122.66 I-.104 J4.406 E.35009
G1 X131.256 Y123.101 E.07766
G1 X130.709 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X130.71 Y123.596 E.00012
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X128.092 Y122.394 I-2.309 J-2.774 E1.66714
G3 X130.31 Y123.225 I-.156 J3.79 E.28815
G1 X130.621 Y123.514 E.05085
M204 S10000
; WIPE_START
G1 F24000
G1 X130.71 Y123.596 E-.17239
G1 X130.71 Y125.475 E-2.67761
; WIPE_END
G1 E-.15 F1800
G1 X123.572 Y128.178 Z6.4 F30000
G1 X122.712 Y128.504 Z6.4
G1 Z6
G1 E3 F1800
; FEATURE: Inner wall
G1 F2451.784
G1 X122.273 Y128.662 E.05577
G1 X122.109 Y128.283 E.04939
G1 X122.621 Y128.02 E.06893
G3 X122.27 Y125.543 I13.407 J-3.164 E.29973
G1 X121.71 Y125.442 E.06814
G1 X121.756 Y125.032 E.04939
G1 X122.332 Y125.06 E.06894
G3 X123.266 Y122.739 I13.192 J3.963 E.29973
G1 X122.831 Y122.372 E.06814
G1 X123.077 Y122.04 E.04939
G1 X123.561 Y122.352 E.06894
G3 X125.531 Y120.809 I9.442 J10.027 E.29973
G1 X125.338 Y120.273 E.06814
G1 X125.716 Y120.109 E.04939
G1 X125.98 Y120.621 E.06894
G3 X128.457 Y120.27 I3.164 J13.407 E.29973
G1 X128.558 Y119.71 E.06814
G1 X128.968 Y119.756 E.04939
G1 X128.94 Y120.332 E.06894
G3 X131.261 Y121.266 I-3.963 J13.192 E.29973
G1 X131.628 Y120.831 E.06813
G1 X131.96 Y121.077 E.04939
G1 X131.648 Y121.561 E.06893
G3 X133.191 Y123.531 I-10.027 J9.442 E.29973
G1 X133.727 Y123.338 E.06814
G1 X133.891 Y123.716 E.04939
G1 X133.379 Y123.98 E.06894
G3 X133.73 Y126.457 I-13.407 J3.164 E.29973
G1 X134.29 Y126.558 E.06814
G1 X134.244 Y126.968 E.04939
G1 X133.668 Y126.94 E.06894
G3 X132.734 Y129.261 I-13.192 J-3.963 E.29973
G1 X133.169 Y129.628 E.06814
G1 X132.923 Y129.96 E.04939
G1 X132.439 Y129.648 E.06894
G3 X130.469 Y131.191 I-9.442 J-10.027 E.29973
G1 X130.662 Y131.727 E.06814
G1 X130.283 Y131.891 E.04939
G1 X130.02 Y131.379 E.06893
G3 X127.543 Y131.73 I-3.164 J-13.407 E.29973
G1 X127.442 Y132.29 E.06814
G1 X127.032 Y132.244 E.04939
G1 X127.06 Y131.668 E.06894
G3 X124.739 Y130.734 I3.964 J-13.193 E.29973
G1 X124.372 Y131.169 E.06814
G1 X124.04 Y130.923 E.04939
G1 X124.352 Y130.439 E.06894
G3 X122.818 Y128.483 I10.028 J-9.443 E.29774
G1 X122.53 Y129.35 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X122.462 Y129.374 E.00864
G3 X119.773 Y129.889 I-2.671 J-6.677 E.32956
G1 X119.704 Y129.74 E.01962
G3 X119.496 Y129.241 I11.047 J-4.903 E.06468
G3 X121.794 Y127.62 I5.528 J5.396 E.33838
G3 X121.588 Y126.166 I9.426 J-2.078 E.17584
G1 X121.517 Y126.153 E.00864
G3 X118.931 Y125.253 I.992 J-7.012 E.32965
G1 X118.946 Y125.091 E.01949
G3 X119.015 Y124.555 I12.02 J1.277 E.06468
G3 X121.816 Y124.3 I2.089 J7.437 E.33838
G3 X122.364 Y122.938 I9.202 J2.913 E.17584
G1 X122.309 Y122.891 E.00864
G3 X120.519 Y120.82 I4.447 J-5.651 E.32956
M73 P80 R2
G1 X120.613 Y120.686 E.01962
G3 X120.941 Y120.256 I9.773 J7.118 E.06468
G3 X123.494 Y121.435 I-1.909 J7.485 E.33838
G3 X124.65 Y120.53 I6.512 J7.123 E.17584
G1 X124.626 Y120.462 E.00864
G3 X124.111 Y117.773 I6.677 J-2.671 E.32956
G1 X124.26 Y117.704 E.01962
G3 X124.759 Y117.496 I4.902 J11.044 E.06468
G3 X126.38 Y119.794 I-5.396 J5.528 E.33838
G3 X127.834 Y119.588 I2.078 J9.426 E.17584
G1 X127.847 Y119.517 E.00864
G3 X128.745 Y116.932 I7.247 J1.071 E.32938
G1 X128.909 Y116.946 E.01965
G3 X129.445 Y117.015 I-1.201 J11.483 E.06469
G3 X129.7 Y119.816 I-7.437 J2.089 E.33838
G3 X131.062 Y120.364 I-2.913 J9.202 E.17584
G1 X131.109 Y120.309 E.00864
G3 X133.18 Y118.519 I5.651 J4.447 E.32956
G1 X133.314 Y118.613 E.01962
G3 X133.744 Y118.941 I-7.117 J9.772 E.06468
G3 X132.565 Y121.494 I-7.485 J-1.909 E.33838
G3 X133.47 Y122.65 I-7.123 J6.512 E.17584
G1 X133.538 Y122.626 E.00864
G3 X136.227 Y122.111 I2.671 J6.677 E.32956
G1 X136.296 Y122.26 E.01962
G3 X136.504 Y122.759 I-11.044 J4.902 E.06468
G3 X134.206 Y124.38 I-5.528 J-5.396 E.33838
G3 X134.412 Y125.834 I-9.426 J2.078 E.17584
G1 X134.483 Y125.847 E.00864
G3 X137.069 Y126.747 I-.992 J7.012 E.32965
G1 X137.054 Y126.909 E.01949
G3 X136.985 Y127.445 I-12.018 J-1.277 E.06468
G3 X134.184 Y127.7 I-2.089 J-7.437 E.33838
G3 X133.636 Y129.062 I-9.202 J-2.913 E.17584
G1 X133.691 Y129.109 E.00864
G3 X135.481 Y131.18 I-4.447 J5.651 E.32956
G1 X135.387 Y131.314 E.01962
G3 X135.059 Y131.744 I-9.773 J-7.118 E.06468
G3 X132.506 Y130.565 I1.909 J-7.485 E.33838
G3 X131.35 Y131.47 I-6.512 J-7.123 E.17584
G1 X131.374 Y131.538 E.00864
G3 X131.889 Y134.227 I-6.677 J2.671 E.32956
G1 X131.74 Y134.296 E.01962
G3 X131.241 Y134.504 I-4.903 J-11.047 E.06468
G3 X129.62 Y132.206 I5.396 J-5.528 E.33838
G3 X128.166 Y132.412 I-2.078 J-9.426 E.17584
G1 X128.153 Y132.483 E.00864
G3 X127.253 Y135.069 I-7.012 J-.992 E.32965
G1 X127.091 Y135.054 E.01949
G3 X126.555 Y134.985 I1.277 J-12.018 E.06468
G3 X126.3 Y132.184 I7.437 J-2.089 E.33838
G3 X124.938 Y131.636 I2.913 J-9.202 E.17584
G1 X124.891 Y131.691 E.00864
G3 X122.82 Y133.481 I-5.651 J-4.447 E.32956
G1 X122.686 Y133.387 E.01962
G3 X122.256 Y133.059 I7.118 J-9.773 E.06468
G3 X123.435 Y130.506 I7.485 J1.909 E.33838
G3 X122.597 Y129.449 I7.123 J-6.512 E.16149
M204 S10000
; WIPE_START
G1 F24000
G1 X122.462 Y129.374 E-.2202
G1 X121.903 Y129.57 E-.84375
G1 X121.226 Y129.746 E-.99768
G1 X120.679 Y129.831 E-.78837
; WIPE_END
G1 E-.15 F1800
G1 X121.854 Y128.619 Z6.4 F30000
G1 Z6
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 1.0808
G1 F1809.127
G2 X121.349 Y128.834 I4.138 J10.419 E.08901
; LINE_WIDTH: 1.04752
G1 F1871.728
G1 X121.218 Y128.89 E.02232
; LINE_WIDTH: 0.998646
G1 F1971.944
G1 X121.087 Y128.945 E.02119
; LINE_WIDTH: 0.97421
G1 F2026.184
G1 X119.976 Y129.449 E.17654
G1 X121.844 Y128.595 F30000
; LINE_WIDTH: 0.83987
G1 F2387.176
G1 X119.974 Y129.442 E.25229
G1 X119.971 Y129.435 F30000
; LINE_WIDTH: 0.66691
G1 F3000
G1 X121.841 Y128.588 E.1944
G1 X121.368 Y125.195 F30000
; LINE_WIDTH: 1.08079
G1 F1809.129
G2 X120.823 Y125.129 I-1.627 J11.098 E.089
; LINE_WIDTH: 1.04752
G1 F1871.719
G1 X120.682 Y125.112 E.02232
; LINE_WIDTH: 0.998648
G1 F1971.938
G1 X120.541 Y125.094 E.02119
; LINE_WIDTH: 0.974211
G1 F2026.183
G1 X119.327 Y124.975 E.17654
; WIPE_START
G1 F24000
G1 X120.541 Y125.094 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X121.002 Y120.776 Z6.4 F30000
G1 Z6
G1 E3 F1800
; LINE_WIDTH: 0.974218
G1 F2026.166
G1 X121.993 Y121.486 E.17654
; LINE_WIDTH: 0.998653
G1 F1971.928
G1 X122.107 Y121.572 E.02119
; LINE_WIDTH: 1.04753
G1 F1871.714
G1 X122.22 Y121.657 E.02232
; LINE_WIDTH: 1.08079
G1 F1809.136
G3 X122.659 Y121.987 I-6.488 J9.086 E.089
G1 X122.675 Y121.966 F30000
; LINE_WIDTH: 0.839875
G1 F2387.158
G1 X121.006 Y120.77 E.25229
G1 X121.01 Y120.764 F30000
; LINE_WIDTH: 0.666905
G1 F3000
G1 X122.679 Y121.96 E.1944
; WIPE_START
G1 F24000
G1 X121.053 Y120.795 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X124.551 Y117.976 Z6.4 F30000
G1 Z6
G1 E3 F1800
; LINE_WIDTH: 0.974208
G1 F2026.189
G1 X125.055 Y119.087 E.17654
; LINE_WIDTH: 0.998648
G1 F1971.939
G1 X125.11 Y119.218 E.02119
; LINE_WIDTH: 1.04752
G1 F1871.717
G1 X125.166 Y119.349 E.02233
; LINE_WIDTH: 1.08079
G1 F1809.131
G3 X125.381 Y119.854 I-10.189 J4.636 E.089
G1 X125.405 Y119.844 F30000
; LINE_WIDTH: 0.839875
G1 F2387.16
G1 X124.558 Y117.974 E.25229
G1 X124.565 Y117.971 F30000
; LINE_WIDTH: 0.666903
G1 F3000
G1 X125.412 Y119.841 E.1944
G1 X128.805 Y119.368 F30000
; LINE_WIDTH: 1.0808
G1 F1809.126
G2 X128.871 Y118.823 I-11.053 J-1.621 E.089
; LINE_WIDTH: 1.04752
G1 F1871.722
G1 X128.888 Y118.682 E.02232
; LINE_WIDTH: 0.998648
G1 F1971.939
G1 X128.906 Y118.541 E.02119
; LINE_WIDTH: 0.974211
G1 F2026.182
G1 X129.025 Y117.327 E.17654
; WIPE_START
G1 F24000
G1 X128.906 Y118.541 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X133.224 Y119.002 Z6.4 F30000
G1 Z6
G1 E3 F1800
; LINE_WIDTH: 0.96895
G1 F2038.253
G1 X132.514 Y119.993 E.17549
; LINE_WIDTH: 0.998647
G1 F1971.941
G1 X132.428 Y120.107 E.02119
; LINE_WIDTH: 1.04753
G1 F1871.713
G1 X132.343 Y120.22 E.02233
; LINE_WIDTH: 1.07696
G1 F1816.137
G3 X132.013 Y120.659 I-9.11 J-6.506 E.08867
G1 X132.034 Y120.675 F30000
; LINE_WIDTH: 0.821571
G1 F2446.55
G1 X133.23 Y119.006 E.24617
G1 X133.236 Y119.01 F30000
; LINE_WIDTH: 0.650373
G1 F3000
G1 X132.04 Y120.679 E.18887
; WIPE_START
G1 F24000
G1 X133.205 Y119.053 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X136.024 Y122.551 Z6.4 F30000
G1 Z6
G1 E3 F1800
; LINE_WIDTH: 0.968956
G1 F2038.24
G1 X134.913 Y123.055 E.17549
; LINE_WIDTH: 0.998652
G1 F1971.929
G1 X134.782 Y123.11 E.02119
; LINE_WIDTH: 1.04753
G1 F1871.714
G1 X134.651 Y123.166 E.02232
; LINE_WIDTH: 1.07695
G1 F1816.14
G3 X134.146 Y123.381 I-4.641 J-10.2 E.08866
G1 X134.156 Y123.405 F30000
; LINE_WIDTH: 0.821549
G1 F2446.622
G1 X136.026 Y122.558 E.24615
G1 X136.029 Y122.565 F30000
; LINE_WIDTH: 0.650384
G1 F3000
G1 X134.159 Y123.412 E.18887
G1 X132.172 Y125.357 F30000
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.821931
G1 F2445.353
G1 X132.186 Y125.957 E.07196
; LINE_WIDTH: 0.861118
G1 F2321.75
G3 X132.2 Y127.414 I-31.244 J1.028 E.18411
G1 X132.644 Y127.583 E.06003
G1 X132.984 Y126.605 E.13089
G1 X132.977 Y126.52 E.01068
; LINE_WIDTH: 0.849887
G1 F2355.879
G1 X132.935 Y125.922 E.07469
; LINE_WIDTH: 0.813049
G1 F2475.22
G1 X132.893 Y125.324 E.07109
G2 X132.666 Y124.127 I-326.721 J61.396 E.14441
G1 X132.172 Y124.282 E.06131
G1 X132.172 Y125.237 E.11318
G1 X132.222 Y123.503 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 0.703372
G1 F2914.83
G1 X132.161 Y123.309 E.02043
; LINE_WIDTH: 0.676136
G1 F3000
G1 X132.1 Y123.116 E.01953
; LINE_WIDTH: 0.640739
G1 X132.061 Y123.023 E.00908
; LINE_WIDTH: 0.622674
G2 X131.852 Y122.774 I-1.171 J.773 E.02851
; LINE_WIDTH: 0.664751
G1 X131.544 Y122.457 E.04172
; LINE_WIDTH: 0.711001
G1 F2879.263
G1 X131.236 Y122.14 E.04506
; LINE_WIDTH: 0.736915
G1 F2764.661
G1 X131.211 Y122.115 E.00374
; LINE_WIDTH: 0.762872
G1 F2658.667
G2 X130.801 Y121.814 I-.916 J.817 E.05647
; LINE_WIDTH: 0.730606
G1 F2791.713
G1 X130.771 Y121.797 E.00366
; LINE_WIDTH: 0.703426
G1 F2914.578
G1 X130.321 Y121.56 E.0512
; LINE_WIDTH: 0.679453
G1 F3000
G2 X129.286 Y121.155 I-2.651 J5.239 E.10763
; LINE_WIDTH: 0.701081
G1 F2925.684
M73 P80 R1
G1 X129.041 Y121.087 E.02552
; LINE_WIDTH: 0.733965
G1 F2777.245
G2 X128.761 Y121.011 I-1.551 J5.148 E.03068
; LINE_WIDTH: 0.759935
G1 F2670.248
G1 X128.609 Y120.978 E.01707
G1 X128.254 Y120.975 E.03904
; LINE_WIDTH: 0.686045
G1 F2998.977
G2 X126.615 Y121.179 I.03 J6.943 E.16192
; LINE_WIDTH: 0.709187
G1 F2887.643
G1 X126.369 Y121.245 E.02587
; LINE_WIDTH: 0.74641
G1 F2724.923
G2 X126.088 Y121.322 I1.274 J5.234 E.03137
; LINE_WIDTH: 0.777258
G1 F2603.349
G1 X126.016 Y121.345 E.00852
; LINE_WIDTH: 0.767666
G1 F2639.973
G1 X125.828 Y121.454 E.02415
; LINE_WIDTH: 0.727302
G1 F2806.093
G2 X125.611 Y121.581 I2.243 J4.09 E.02624
; LINE_WIDTH: 0.684537
G1 F3000
G2 X124.333 Y122.572 I3.472 J5.795 E.15821
; LINE_WIDTH: 0.718534
G1 F2844.978
G1 X124.154 Y122.754 E.02627
; LINE_WIDTH: 0.76009
G1 F2669.637
G2 X123.951 Y122.964 I1.397 J1.56 E.03214
; LINE_WIDTH: 0.762358
G1 F2660.685
G1 X123.825 Y123.185 E.0281
; LINE_WIDTH: 0.719769
G1 F2839.436
G2 X123.684 Y123.437 I4.597 J2.745 E.02976
; LINE_WIDTH: 0.684568
G1 F3000
G2 X123.089 Y124.941 I6.049 J3.265 E.15825
; LINE_WIDTH: 0.727226
G1 F2806.427
G1 X123.033 Y125.166 E.02424
; LINE_WIDTH: 0.768476
G1 F2636.842
G2 X122.974 Y125.474 I.708 J.294 E.03516
; LINE_WIDTH: 0.748531
G1 F2716.201
G1 X122.978 Y125.729 E.02751
; LINE_WIDTH: 0.710237
G1 F2882.784
G2 X122.984 Y126.016 I5.337 J.037 E.02925
; LINE_WIDTH: 0.685427
G1 F3000
G2 X123.237 Y127.615 I6.918 J-.277 E.15854
; LINE_WIDTH: 0.735278
G1 F2771.631
G1 X123.292 Y127.799 E.02034
; LINE_WIDTH: 0.769867
G1 F2631.477
G2 X123.424 Y128.126 I1.036 J-.229 E.03949
; LINE_WIDTH: 0.735965
G1 F2768.699
G1 X123.557 Y128.344 E.02697
; LINE_WIDTH: 0.688673
G1 F2985.905
G2 X124.715 Y129.812 I5.721 J-3.323 E.18432
; LINE_WIDTH: 0.726333
G1 F2810.338
G1 X124.739 Y129.836 E.00361
; LINE_WIDTH: 0.743964
G1 F2735.05
G1 X124.851 Y129.94 E.01636
; LINE_WIDTH: 0.770031
G1 F2630.846
G2 X125.138 Y130.151 I.642 J-.573 E.04003
; LINE_WIDTH: 0.741602
G1 F2744.901
G1 X125.169 Y130.169 E.00379
; LINE_WIDTH: 0.72465
G1 F2817.744
G1 X125.393 Y130.289 E.02649
; LINE_WIDTH: 0.682489
G1 F3000
G2 X126.647 Y130.825 I2.922 J-5.103 E.13294
; LINE_WIDTH: 0.694968
G1 F2955.047
G1 X126.892 Y130.894 E.02526
; LINE_WIDTH: 0.724045
G1 F2820.414
G2 X127.171 Y130.972 I1.582 J-5.12 E.03014
; LINE_WIDTH: 0.762736
G1 F2659.202
G2 X127.676 Y131.026 I.379 J-1.168 E.05646
; LINE_WIDTH: 0.729209
G1 F2797.776
G1 X127.711 Y131.025 E.00365
; LINE_WIDTH: 0.691044
G1 F2974.209
G2 X128.703 Y130.957 I-.198 J-10.096 E.09808
; LINE_WIDTH: 0.679908
G1 F3000
G1 X128.788 Y130.945 E.00833
M73 P81 R1
G2 X129.318 Y130.837 I-6.123 J-31.47 E.05233
; LINE_WIDTH: 0.701977
G1 F2921.433
G1 X129.564 Y130.773 E.02556
; LINE_WIDTH: 0.735375
G1 F2771.217
G2 X129.845 Y130.698 I-1.236 J-5.233 E.03076
; LINE_WIDTH: 0.759326
G1 F2672.666
G1 X129.984 Y130.654 E.01601
G1 X130.301 Y130.473 E.04004
; LINE_WIDTH: 0.689893
G1 F2979.877
G2 X131.216 Y129.839 I-4.679 J-7.721 E.10969
G1 X132.074 Y129.06 E.11406
; LINE_WIDTH: 0.717923
G1 F2847.732
G1 X132.368 Y128.287 E.08522
G1 X133.321 Y130.04 F30000
; LINE_WIDTH: 0.650389
G1 F3000
G1 X134.99 Y131.236 E.18888
G1 X134.994 Y131.23 F30000
; LINE_WIDTH: 0.82156
G1 F2446.587
G1 X133.325 Y130.034 E.24616
G1 X133.341 Y130.013 F30000
; LINE_WIDTH: 1.07696
G1 F1816.134
G2 X133.78 Y130.343 I6.948 J-8.784 E.08866
; LINE_WIDTH: 1.04753
G1 F1871.713
G1 X133.893 Y130.428 E.02233
; LINE_WIDTH: 0.998647
G1 F1971.941
G1 X134.007 Y130.514 E.02119
; LINE_WIDTH: 0.968954
G1 F2038.243
G1 X134.998 Y131.224 E.17549
; WIPE_START
G1 F24000
G1 X134.007 Y130.514 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X134.632 Y126.805 Z6.4 F30000
G1 Z6
G1 E3 F1800
; LINE_WIDTH: 1.07696
G1 F1816.134
G2 X135.177 Y126.871 I1.626 J-11.093 E.08866
; LINE_WIDTH: 1.04752
G1 F1871.72
G1 X135.318 Y126.888 E.02232
; LINE_WIDTH: 0.998651
G1 F1971.932
G1 X135.459 Y126.906 E.02119
; LINE_WIDTH: 0.967426
G1 F2041.776
G1 X136.673 Y127.025 E.17519
; WIPE_START
G1 F24000
G1 X135.459 Y126.906 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X131.712 Y133.555 Z6.4 F30000
G1 X131.449 Y134.024 Z6.4
G1 Z6
G1 E3 F1800
; LINE_WIDTH: 0.968955
G1 F2038.242
G1 X130.945 Y132.913 E.17549
; LINE_WIDTH: 0.99865
G1 F1971.934
G1 X130.89 Y132.782 E.02119
; LINE_WIDTH: 1.04752
G1 F1871.726
G1 X130.834 Y132.651 E.02232
; LINE_WIDTH: 1.07695
G1 F1816.14
G3 X130.619 Y132.146 I10.207 J-4.644 E.08867
G1 X130.595 Y132.156 F30000
; LINE_WIDTH: 0.821559
G1 F2446.59
G1 X131.442 Y134.026 E.24616
G1 X131.435 Y134.029 F30000
; LINE_WIDTH: 0.65038
G1 F3000
G1 X130.588 Y132.159 E.18887
G1 X127.195 Y132.632 F30000
; LINE_WIDTH: 1.08079
G1 F1809.13
G2 X127.129 Y133.177 I11.091 J1.626 E.089
; LINE_WIDTH: 1.04752
G1 F1871.723
G1 X127.112 Y133.318 E.02232
; LINE_WIDTH: 0.99865
G1 F1971.933
G1 X127.094 Y133.459 E.02119
; LINE_WIDTH: 0.974214
G1 F2026.174
G1 X126.975 Y134.673 E.17654
; WIPE_START
G1 F24000
G1 X127.094 Y133.459 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.96 Y131.321 Z6.4 F30000
G1 Z6
G1 E3 F1800
; LINE_WIDTH: 0.666894
G1 F3000
G1 X122.764 Y132.99 E.1944
G1 X122.77 Y132.994 F30000
; LINE_WIDTH: 0.839877
G1 F2387.155
G1 X123.966 Y131.325 E.25228
G1 X123.987 Y131.341 F30000
; LINE_WIDTH: 1.08079
G1 F1809.132
G2 X123.657 Y131.78 I8.793 J6.954 E.08901
; LINE_WIDTH: 1.04752
G1 F1871.732
G1 X123.572 Y131.893 E.02232
; LINE_WIDTH: 0.998645
G1 F1971.944
G1 X123.486 Y132.007 E.02119
; LINE_WIDTH: 0.974211
G1 F2026.183
G1 X122.776 Y132.998 E.17654
; CHANGE_LAYER
; Z_HEIGHT: 6.4
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X123.486 Y132.007 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 16/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L16
M991 S0 P15 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z6.4 I.909 J.809 P1  F30000
G1 X131.344 Y123.183 Z6.4
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2451.784
G1 X131.444 Y123.276 E.01637
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X128.06 Y121.66 I-2.777 J-3.338 E1.99934
G3 X130.78 Y122.66 I-.073 J4.399 E.35339
G1 X131.256 Y123.101 E.07766
G1 X130.709 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X130.71 Y123.596 E.00011
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X128.065 Y122.394 I-2.307 J-2.774 E1.66294
G1 X128.17 Y122.393 E.01255
G3 X130.312 Y123.223 I-.217 J3.743 E.27931
G1 X130.622 Y123.514 E.05088
M204 S10000
; WIPE_START
G1 F24000
G1 X130.71 Y123.596 E-.17233
G1 X130.71 Y125.475 E-2.67767
; WIPE_END
G1 E-.15 F1800
G1 X123.625 Y128.313 Z6.8 F30000
G1 X122.771 Y128.655 Z6.8
G1 Z6.4
G1 E3 F1800
; FEATURE: Inner wall
G1 F2451.784
G1 X122.334 Y128.826 E.05621
G1 X122.159 Y128.453 E.0493
G1 X122.673 Y128.168 E.07029
G3 X122.245 Y125.7 I16.724 J-4.166 E.29995
G1 X121.68 Y125.614 E.06839
G1 X121.715 Y125.204 E.0493
G1 X122.302 Y125.214 E.07029
G3 X123.166 Y122.863 I16.565 J4.754 E.29995
G1 X122.72 Y122.506 E.0684
G1 X122.955 Y122.168 E.0493
G1 X123.459 Y122.47 E.07029
G3 X125.382 Y120.866 I11.971 J12.401 E.29995
G1 X125.174 Y120.334 E.06839
G1 X125.547 Y120.159 E.0493
G1 X125.832 Y120.673 E.07029
G3 X128.3 Y120.245 I4.166 J16.725 E.29995
G1 X128.386 Y119.68 E.06839
G1 X128.796 Y119.715 E.0493
G1 X128.786 Y120.302 E.07029
G3 X131.137 Y121.166 I-4.754 J16.566 E.29995
G1 X131.494 Y120.72 E.06839
G1 X131.832 Y120.955 E.0493
G1 X131.53 Y121.459 E.07029
G3 X133.134 Y123.382 I-12.401 J11.971 E.29995
G1 X133.666 Y123.174 E.0684
G1 X133.841 Y123.547 E.0493
G1 X133.327 Y123.832 E.07029
G3 X133.755 Y126.3 I-16.724 J4.166 E.29995
G1 X134.32 Y126.386 E.06839
G1 X134.285 Y126.796 E.0493
G1 X133.698 Y126.786 E.07029
G3 X132.834 Y129.137 I-16.569 J-4.755 E.29995
G1 X133.28 Y129.494 E.06839
G1 X133.045 Y129.832 E.0493
G1 X132.541 Y129.53 E.07029
G3 X130.618 Y131.134 I-11.971 J-12.401 E.29995
G1 X130.826 Y131.666 E.06839
G1 X130.453 Y131.841 E.0493
G1 X130.168 Y131.327 E.07029
G3 X127.7 Y131.755 I-4.166 J-16.724 E.29995
G1 X127.614 Y132.32 E.06839
G1 X127.204 Y132.285 E.0493
G1 X127.214 Y131.698 E.07029
G3 X124.863 Y130.834 I4.754 J-16.567 E.29995
G1 X124.506 Y131.28 E.0684
G1 X124.168 Y131.045 E.0493
G1 X124.47 Y130.541 E.07029
G3 X122.877 Y128.632 I12.403 J-11.972 E.29778
G1 X122.619 Y129.503 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X122.556 Y129.528 E.00816
G3 X119.883 Y130.114 I-2.841 J-6.567 E.32936
G3 X119.811 Y129.97 I1.611 J-.902 E.01927
G3 X119.592 Y129.476 I5.154 J-2.585 E.06465
G3 X121.839 Y127.791 I5.685 J5.239 E.33796
G3 X121.589 Y126.343 I11.711 J-2.768 E.17593
G1 X121.521 Y126.333 E.00816
G3 X118.914 Y125.504 I.863 J-7.234 E.32929
G3 X118.923 Y125.342 I1.865 J.026 E.01946
G3 X118.98 Y124.806 I5.739 J.338 E.06445
G3 X121.769 Y124.47 I2.304 J7.38 E.33796
G3 X122.276 Y123.091 I11.526 J3.458 E.17593
G1 X122.223 Y123.049 E.00816
G3 X120.379 Y121.028 I4.267 J-5.744 E.32936
G3 X120.467 Y120.893 I1.586 J.944 E.01927
G3 X120.785 Y120.456 I4.816 J3.171 E.06464
G3 X123.368 Y121.56 I-1.695 J7.543 E.33796
G3 X124.497 Y120.619 I8.254 J8.759 E.17593
G1 X124.472 Y120.556 E.00816
G3 X123.886 Y117.883 I6.567 J-2.841 E.32936
G3 X124.03 Y117.811 I.902 J1.611 E.01927
G3 X124.524 Y117.592 I2.585 J5.155 E.06464
G3 X126.209 Y119.839 I-5.239 J5.685 E.33796
G3 X127.657 Y119.589 I2.768 J11.712 E.17593
G1 X127.667 Y119.521 E.00816
G3 X128.496 Y116.914 I7.234 J.863 E.32929
G1 X128.529 Y116.915 E.00401
G3 X128.657 Y116.923 I-.026 J1.486 E.01526
G3 X129.194 Y116.98 I-.338 J5.756 E.06464
G3 X129.53 Y119.769 I-7.38 J2.304 E.33796
G3 X130.909 Y120.276 I-3.459 J11.527 E.17593
G1 X130.951 Y120.223 E.00815
G3 X132.972 Y118.379 I5.744 J4.266 E.32936
G3 X133.107 Y118.467 I-.944 J1.586 E.01927
G3 X133.544 Y118.785 I-3.171 J4.816 E.06464
G3 X132.44 Y121.368 I-7.543 J-1.695 E.33796
G3 X133.381 Y122.497 I-8.759 J8.254 E.17593
G1 X133.444 Y122.472 E.00816
G3 X136.117 Y121.886 I2.841 J6.567 E.32936
G3 X136.189 Y122.03 I-1.612 J.902 E.01927
G3 X136.408 Y122.524 I-5.154 J2.585 E.06465
G3 X134.161 Y124.209 I-5.685 J-5.239 E.33796
G3 X134.411 Y125.657 I-11.712 J2.768 E.17593
G1 X134.479 Y125.667 E.00816
G3 X137.086 Y126.496 I-.863 J7.234 E.32929
G3 X137.077 Y126.658 I-1.865 J-.026 E.01946
G3 X137.02 Y127.194 I-5.739 J-.338 E.06445
G3 X134.231 Y127.53 I-2.304 J-7.38 E.33796
G3 X133.724 Y128.909 I-11.528 J-3.459 E.17593
G1 X133.777 Y128.951 E.00815
G3 X135.621 Y130.972 I-4.266 J5.744 E.32936
G3 X135.533 Y131.107 I-1.586 J-.944 E.01927
G3 X135.215 Y131.544 I-4.816 J-3.171 E.06464
G3 X132.632 Y130.44 I1.695 J-7.543 E.33796
G3 X131.503 Y131.381 I-8.253 J-8.759 E.17593
G1 X131.528 Y131.444 E.00816
G3 X132.114 Y134.117 I-6.566 J2.841 E.32936
G3 X131.97 Y134.189 I-.902 J-1.611 E.01927
G3 X131.476 Y134.408 I-2.585 J-5.154 E.06464
G3 X129.791 Y132.161 I5.239 J-5.685 E.33796
G3 X128.343 Y132.411 I-2.768 J-11.711 E.17593
G1 X128.333 Y132.479 E.00816
G3 X127.504 Y135.086 I-7.234 J-.863 E.32929
G3 X127.342 Y135.077 I.025 J-1.864 E.01946
G3 X126.806 Y135.02 I.337 J-5.739 E.06445
G3 X126.47 Y132.231 I7.38 J-2.304 E.33796
G3 X125.091 Y131.724 I3.459 J-11.527 E.17593
G1 X125.049 Y131.777 E.00816
G3 X123.028 Y133.621 I-5.744 J-4.267 E.32936
G3 X122.893 Y133.533 I.945 J-1.587 E.01927
G3 X122.456 Y133.215 I3.171 J-4.816 E.06464
G3 X123.56 Y130.632 I7.543 J1.695 E.33796
G3 X122.69 Y129.599 I8.759 J-8.254 E.16157
M204 S10000
; WIPE_START
G1 F24000
G1 X122.556 Y129.528 E-.2177
G1 X122.006 Y129.737 E-.83842
G1 X121.333 Y129.932 E-.99757
G1 X120.784 Y130.033 E-.79631
; WIPE_END
G1 E-.15 F1800
G1 X121.914 Y128.796 Z6.8 F30000
G1 Z6.4
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 1.07844
G1 F1813.414
G2 X121.432 Y129.017 I4.273 J9.946 E.08586
; LINE_WIDTH: 1.04707
G1 F1872.599
G1 X121.302 Y129.076 E.02231
; LINE_WIDTH: 0.998205
G1 F1972.897
G1 X121.173 Y129.136 E.02118
; LINE_WIDTH: 0.973771
G1 F2027.186
G1 X120.076 Y129.67 E.1765
G1 X121.903 Y128.772 F30000
; LINE_WIDTH: 0.839459
G1 F2388.476
G1 X120.073 Y129.663 E.24997
G1 X120.07 Y129.657 F30000
; LINE_WIDTH: 0.666516
M73 P82 R1
G1 F3000
G1 X121.9 Y128.765 E.1926
G1 X121.331 Y125.382 F30000
; LINE_WIDTH: 1.07912
G1 F1812.179
G2 X120.811 Y125.33 I-1.329 J10.635 E.08462
; LINE_WIDTH: 1.05754
G1 F1852.426
G1 X120.714 Y125.32 E.01546
; LINE_WIDTH: 1.02403
G1 F1918.582
G1 X120.617 Y125.311 E.01493
; LINE_WIDTH: 0.976257
G1 F2021.526
G2 X119.303 Y125.216 I-2.602 J26.85 E.19118
; WIPE_START
G1 F24000
G1 X120.617 Y125.311 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X120.86 Y120.973 Z6.8 F30000
G1 Z6.4
G1 E3 F1800
; LINE_WIDTH: 0.973766
G1 F2027.198
G1 X121.871 Y121.655 E.17649
; LINE_WIDTH: 0.998199
G1 F1972.908
G1 X121.987 Y121.738 E.02118
; LINE_WIDTH: 1.04706
G1 F1872.614
G1 X122.103 Y121.82 E.02231
; LINE_WIDTH: 1.07844
G1 F1813.412
G3 X122.536 Y122.127 I-6.059 J9.003 E.08587
G1 X122.551 Y122.106 F30000
; LINE_WIDTH: 0.839469
G1 F2388.445
G1 X120.864 Y120.967 E.24997
G1 X120.868 Y120.961 F30000
; LINE_WIDTH: 0.666516
G1 F3000
G1 X122.555 Y122.1 E.1926
; WIPE_START
G1 F24000
G1 X120.898 Y120.981 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X124.33 Y118.076 Z6.8 F30000
G1 Z6.4
G1 E3 F1800
; LINE_WIDTH: 0.973775
G1 F2027.176
G1 X124.864 Y119.173 E.1765
; LINE_WIDTH: 0.998208
G1 F1972.889
G1 X124.924 Y119.302 E.02118
; LINE_WIDTH: 1.04707
G1 F1872.597
G1 X124.983 Y119.432 E.02231
; LINE_WIDTH: 1.07844
G1 F1813.416
G3 X125.204 Y119.914 I-9.724 J4.755 E.08587
G1 X125.228 Y119.903 F30000
; LINE_WIDTH: 0.839459
G1 F2388.476
G1 X124.337 Y118.073 E.24997
G1 X124.343 Y118.07 F30000
; LINE_WIDTH: 0.666516
G1 F3000
G1 X125.235 Y119.9 E.1926
G1 X128.618 Y119.331 F30000
; LINE_WIDTH: 1.07912
G1 F1812.183
G2 X128.67 Y118.811 I-10.559 J-1.322 E.08462
; LINE_WIDTH: 1.05754
G1 F1852.427
G1 X128.68 Y118.714 E.01546
; LINE_WIDTH: 1.02403
G1 F1918.583
G1 X128.689 Y118.617 E.01493
; LINE_WIDTH: 0.976257
G1 F2021.526
G2 X128.784 Y117.303 I-26.857 J-2.603 E.19118
; WIPE_START
G1 F24000
G1 X128.689 Y118.617 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X133.027 Y118.86 Z6.8 F30000
G1 Z6.4
G1 E3 F1800
; LINE_WIDTH: 0.968515
G1 F2039.257
G1 X132.345 Y119.871 E.17545
; LINE_WIDTH: 0.998196
G1 F1972.915
G1 X132.262 Y119.987 E.02118
; LINE_WIDTH: 1.04706
G1 F1872.616
G1 X132.18 Y120.103 E.02231
; LINE_WIDTH: 1.07649
G1 F1816.984
G3 X131.873 Y120.536 I-8.963 J-6.032 E.0857
G1 X131.894 Y120.551 F30000
; LINE_WIDTH: 0.821144
G1 F2447.97
G1 X133.033 Y118.864 E.24389
G1 X133.039 Y118.868 F30000
; LINE_WIDTH: 0.650009
G1 F3000
G1 X131.9 Y120.555 E.18713
; WIPE_START
G1 F24000
G1 X133.019 Y118.898 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X135.924 Y122.33 Z6.8 F30000
G1 Z6.4
G1 E3 F1800
; LINE_WIDTH: 0.968512
G1 F2039.265
G1 X134.827 Y122.864 E.17545
; LINE_WIDTH: 0.998197
G1 F1972.913
G1 X134.698 Y122.924 E.02118
; LINE_WIDTH: 1.04707
G1 F1872.604
G1 X134.568 Y122.983 E.02231
; LINE_WIDTH: 1.07649
G1 F1816.992
G3 X134.086 Y123.204 I-4.751 J-9.715 E.0857
G1 X134.097 Y123.228 F30000
; LINE_WIDTH: 0.821151
G1 F2447.945
G1 X135.927 Y122.337 E.24389
G1 X135.93 Y122.343 F30000
; LINE_WIDTH: 0.649991
G1 F3000
G1 X134.1 Y123.235 E.18712
G1 X132.225 Y123.479 F30000
; LINE_WIDTH: 0.687831
G1 F2990.084
G1 X132.102 Y123.116 E.03767
; LINE_WIDTH: 0.653014
G1 F3000
G1 X132.046 Y123.02 E.01029
; LINE_WIDTH: 0.632693
G2 X131.752 Y122.672 I-1.434 J.913 E.04067
; LINE_WIDTH: 0.671971
G1 X131.491 Y122.409 E.03541
; LINE_WIDTH: 0.704651
G1 F2908.809
G2 X131.206 Y122.122 I-5.455 J5.143 E.04085
; LINE_WIDTH: 0.742318
G1 F2741.907
G1 X131.06 Y121.989 E.02107
; LINE_WIDTH: 0.78017
G1 F2592.43
G2 X130.78 Y121.782 I-.712 J.668 E.03965
; LINE_WIDTH: 0.745597
G1 F2728.282
G1 X130.552 Y121.668 E.02738
; LINE_WIDTH: 0.708284
G1 F2891.83
G2 X130.294 Y121.54 I-2.496 J4.712 E.02915
; LINE_WIDTH: 0.679926
G1 F3000
G2 X129.286 Y121.158 I-2.767 J5.777 E.10458
; LINE_WIDTH: 0.691876
G1 F2970.125
G1 X129.04 Y121.093 E.02512
; LINE_WIDTH: 0.719094
G1 F2842.463
G2 X128.76 Y121.02 I-1.493 J5.144 E.02986
; LINE_WIDTH: 0.751579
G1 F2703.766
G1 X128.606 Y120.988 E.01706
; LINE_WIDTH: 0.78065
G1 F2590.637
G2 X128.255 Y120.959 I-.241 J.773 E.04016
; LINE_WIDTH: 0.752067
G1 F2701.784
G1 X128.219 Y120.96 E.00391
; LINE_WIDTH: 0.733311
G1 F2780.05
G1 X127.965 Y120.978 E.02686
; LINE_WIDTH: 0.683858
G1 F3000
G2 X126.616 Y121.183 I.271 J6.315 E.13327
; LINE_WIDTH: 0.698353
G1 F2938.715
G1 X126.371 Y121.251 E.0254
; LINE_WIDTH: 0.729889
G1 F2794.822
G2 X126.092 Y121.331 I1.324 J5.205 E.03046
; LINE_WIDTH: 0.761511
G1 F2664.022
G1 X125.981 Y121.368 E.01293
; LINE_WIDTH: 0.776073
G1 F2607.819
G2 X125.633 Y121.549 I.233 J.871 E.04443
; LINE_WIDTH: 0.738703
G1 F2757.09
G1 X125.604 Y121.568 E.00376
; LINE_WIDTH: 0.722284
G1 F2828.217
G1 X125.394 Y121.712 E.02639
; LINE_WIDTH: 0.682695
G1 F3000
G2 X124.337 Y122.575 I3.529 J5.398 E.13299
; LINE_WIDTH: 0.70607
G1 F2902.154
G1 X124.16 Y122.759 E.02574
; LINE_WIDTH: 0.74194
G1 F2743.489
G2 X123.959 Y122.969 I3.786 J3.824 E.03113
; LINE_WIDTH: 0.769582
G1 F2632.576
G1 X123.857 Y123.086 E.01728
G1 X123.689 Y123.4 E.03966
; LINE_WIDTH: 0.726599
G1 F2809.171
G1 X123.673 Y123.431 E.00362
; LINE_WIDTH: 0.691095
G1 F2973.954
G2 X123.308 Y124.261 I8.075 J4.052 E.08952
; LINE_WIDTH: 0.682021
G1 F3000
G1 X123.248 Y124.423 E.01679
G2 X123.095 Y124.942 I9.532 J3.1 E.05257
; LINE_WIDTH: 0.715029
G1 F2860.827
G1 X123.035 Y125.19 E.02612
; LINE_WIDTH: 0.755253
G1 F2688.928
G2 X122.968 Y125.474 I5.218 J1.381 E.03187
; LINE_WIDTH: 0.788096
G1 F2563.171
G1 X122.955 Y125.548 E.00861
; LINE_WIDTH: 0.77772
G1 F2601.611
G1 X122.963 Y125.765 E.02455
; LINE_WIDTH: 0.734881
G1 F2773.325
G2 X122.973 Y126.017 I4.675 J-.068 E.02663
; LINE_WIDTH: 0.686215
G1 F2998.128
G2 X123.244 Y127.613 I7.294 J-.415 E.15869
; LINE_WIDTH: 0.725253
G1 F2815.085
G1 X123.318 Y127.856 E.02656
; LINE_WIDTH: 0.76982
G1 F2631.66
G2 X123.405 Y128.136 I1.857 J-.428 E.03269
; LINE_WIDTH: 0.772105
G1 F2622.897
G1 X123.543 Y128.351 E.02851
; LINE_WIDTH: 0.726713
G1 F2808.671
G2 X123.699 Y128.593 I4.58 J-2.779 E.03013
; LINE_WIDTH: 0.686243
G1 F2997.992
G2 X124.744 Y129.83 I6.156 J-4.141 E.15873
; LINE_WIDTH: 0.734678
G1 F2774.195
G1 X124.915 Y129.987 E.02453
; LINE_WIDTH: 0.778651
G1 F2598.114
G2 X125.159 Y130.185 I.574 J-.458 E.03578
; LINE_WIDTH: 0.757452
G1 F2680.122
G1 X125.386 Y130.301 E.02789
; LINE_WIDTH: 0.716362
G1 F2854.781
G2 X125.643 Y130.43 I2.532 J-4.701 E.02958
; LINE_WIDTH: 0.686425
G1 F2997.081
G1 X126.108 Y130.636 E.04975
G2 X127.139 Y130.956 I3.29 J-8.771 E.10572
; LINE_WIDTH: 0.722383
G1 F2827.776
G1 X127.172 Y130.964 E.00357
; LINE_WIDTH: 0.743387
G1 F2737.45
G1 X127.36 Y131.004 E.0206
; LINE_WIDTH: 0.780099
G1 F2592.696
G2 X127.711 Y131.042 I.284 J-.975 E.04016
; LINE_WIDTH: 0.744064
G1 F2734.633
G1 X127.965 Y131.027 E.02732
; LINE_WIDTH: 0.693066
G1 F2964.304
G2 X128.67 Y130.96 I-.298 J-6.895 E.07007
; LINE_WIDTH: 0.677578
G1 F3000
G1 X128.788 Y130.944 E.01149
G2 X129.317 Y130.834 I-5.936 J-29.757 E.05209
; LINE_WIDTH: 0.69258
G1 F2966.677
G1 X129.562 Y130.767 E.02516
; LINE_WIDTH: 0.720313
G1 F2837.003
G2 X129.841 Y130.69 I-1.284 J-5.199 E.02993
; LINE_WIDTH: 0.752731
G1 F2699.094
G1 X129.986 Y130.642 E.01657
; LINE_WIDTH: 0.780269
G1 F2592.061
G2 X130.308 Y130.488 I-.184 J-.8 E.04068
; LINE_WIDTH: 0.750419
G1 F2708.485
G1 X130.338 Y130.469 E.00389
; LINE_WIDTH: 0.73194
G1 F2785.949
G1 X130.549 Y130.327 E.0268
; LINE_WIDTH: 0.684075
G1 F3000
G2 X132.016 Y129.105 I-5.597 J-8.209 E.18645
; LINE_WIDTH: 0.709283
G1 F2887.194
G1 X132.085 Y129.013 E.01165
; LINE_WIDTH: 0.752462
G1 F2700.182
G1 X132.153 Y128.921 E.01245
; LINE_WIDTH: 0.774052
G1 F2615.477
G1 X132.301 Y128.271 E.07475
G1 X132.207 Y126.413 F30000
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.876443
G1 F2276.746
G1 X132.207 Y127.468 E.13595
G1 X132.644 Y127.567 E.05775
G1 X133.006 Y126.449 E.15144
G1 X132.994 Y126.36 E.01155
; LINE_WIDTH: 0.85682
G1 F2334.692
G1 X132.935 Y125.773 E.07416
; LINE_WIDTH: 0.801601
G1 F2514.807
G1 X132.876 Y125.186 E.06885
G2 X132.645 Y124.101 I-406.569 J85.903 E.12943
G1 X132.167 Y124.262 E.05889
G1 X132.167 Y125.233 E.11321
; LINE_WIDTH: 0.817576
G1 F2459.906
G1 X132.185 Y125.763 E.06323
; LINE_WIDTH: 0.837198
G1 F2395.664
G1 X132.203 Y126.293 E.06493
G1 X134.669 Y126.618 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 1.07142
G1 F1826.344
G2 X135.189 Y126.67 I1.328 J-10.626 E.08397
G1 X135.286 Y126.68 E.01568
; LINE_WIDTH: 1.02403
G1 F1918.585
G1 X135.383 Y126.689 E.01493
; LINE_WIDTH: 0.990526
G1 F1989.642
G1 X135.48 Y126.698 E.0144
; LINE_WIDTH: 0.966981
G1 F2042.808
G1 X136.697 Y126.784 E.17515
; WIPE_START
G1 F24000
G1 X135.48 Y126.698 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X135.14 Y131.027 Z6.8 F30000
G1 Z6.4
G1 E3 F1800
; LINE_WIDTH: 0.968522
G1 F2039.242
G1 X134.129 Y130.345 E.17545
; LINE_WIDTH: 0.998203
G1 F1972.902
G1 X134.013 Y130.262 E.02117
; LINE_WIDTH: 1.04707
G1 F1872.61
G1 X133.897 Y130.18 E.02231
; LINE_WIDTH: 1.0765
G1 F1816.981
G3 X133.464 Y129.873 I6.049 J-8.988 E.0857
G1 X133.449 Y129.894 F30000
; LINE_WIDTH: 0.821139
G1 F2447.987
G1 X135.136 Y131.033 E.24389
G1 X135.132 Y131.039 F30000
; LINE_WIDTH: 0.650009
G1 F3000
G1 X133.445 Y129.9 E.18713
; WIPE_START
G1 F24000
G1 X135.102 Y131.019 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X131.67 Y133.924 Z6.8 F30000
G1 Z6.4
G1 E3 F1800
; LINE_WIDTH: 0.968514
G1 F2039.261
G1 X131.136 Y132.827 E.17545
; LINE_WIDTH: 0.998202
G1 F1972.902
G1 X131.076 Y132.698 E.02118
; LINE_WIDTH: 1.04707
G1 F1872.596
G1 X131.017 Y132.568 E.02231
; LINE_WIDTH: 1.07649
G1 F1816.995
G3 X130.796 Y132.086 I9.749 J-4.767 E.0857
G1 X130.772 Y132.097 F30000
; LINE_WIDTH: 0.821151
G1 F2447.946
G1 X131.663 Y133.927 E.2439
G1 X131.657 Y133.93 F30000
; LINE_WIDTH: 0.649993
G1 F3000
G1 X130.765 Y132.1 E.18712
G1 X127.382 Y132.669 F30000
; LINE_WIDTH: 1.07912
G1 F1812.177
G2 X127.33 Y133.189 I10.546 J1.321 E.08463
; LINE_WIDTH: 1.05753
G1 F1852.449
G1 X127.32 Y133.286 E.01546
; LINE_WIDTH: 1.02403
G1 F1918.595
G1 X127.311 Y133.383 E.01493
; LINE_WIDTH: 0.976261
G1 F2021.518
G2 X127.216 Y134.697 I26.825 J2.6 E.19118
; WIPE_START
G1 F24000
G1 X127.311 Y133.383 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X124.1 Y131.445 Z6.8 F30000
G1 Z6.4
G1 E3 F1800
; LINE_WIDTH: 0.666515
G1 F3000
G1 X122.961 Y133.132 E.1926
G1 X122.967 Y133.136 F30000
; LINE_WIDTH: 0.839466
G1 F2388.454
G1 X124.106 Y131.449 E.24996
G1 X124.127 Y131.464 F30000
; LINE_WIDTH: 1.07844
G1 F1813.412
G2 X123.82 Y131.897 I8.691 J6.489 E.08587
; LINE_WIDTH: 1.04707
G1 F1872.612
G1 X123.738 Y132.013 E.02231
; LINE_WIDTH: 0.9982
G1 F1972.907
G1 X123.655 Y132.129 E.02118
; LINE_WIDTH: 0.973766
G1 F2027.198
G1 X122.973 Y133.14 E.17649
; CHANGE_LAYER
; Z_HEIGHT: 6.8
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X123.655 Y132.129 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 17/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L17
M991 S0 P16 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z6.8 I.923 J.793 P1  F30000
G1 X131.344 Y123.183 Z6.8
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2420
G1 X131.444 Y123.276 E.01637
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X126.102 Y129.903 I-2.777 J-3.361 E.5956
G1 X126.102 Y129.903 E0
G3 X128.032 Y121.66 I1.891 J-3.905 E1.40138
G3 X130.78 Y122.66 I-.042 J4.394 E.35668
G1 X131.256 Y123.101 E.07765
G1 X130.709 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2420
G1 X130.71 Y123.596 E.0001
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X128.037 Y122.394 I-2.307 J-2.773 E1.65958
G1 X128.17 Y122.393 E.01586
G3 X130.312 Y123.223 I-.217 J3.743 E.27931
G1 X130.622 Y123.514 E.05089
M204 S10000
; WIPE_START
G1 F24000
G1 X130.71 Y123.596 E-.17219
G1 X130.71 Y125.475 E-2.67781
; WIPE_END
G1 E-.15 F1800
G1 X123.953 Y129.024 Z7.2 F30000
G1 X123.406 Y129.311 Z7.2
G1 Z6.8
G1 E3 F1800
; FEATURE: Inner wall
G1 F2420
G1 X122.975 Y128.76 E.08376
G1 X122.474 Y128.963 E.06468
G1 X122.295 Y128.588 E.04966
G1 X122.745 Y128.34 E.06149
G3 X122.268 Y125.877 I12.55 J-3.707 E.3006
G1 X121.733 Y125.803 E.06467
G1 X121.765 Y125.389 E.04966
G1 X122.279 Y125.399 E.06148
G3 X123.097 Y123.028 I12.721 J3.064 E.3006
G1 X122.671 Y122.696 E.06467
G1 X122.906 Y122.353 E.04966
G1 X123.346 Y122.619 E.06148
G3 X125.24 Y120.975 I9.485 J9.014 E.3006
G1 X125.037 Y120.474 E.06468
G1 X125.412 Y120.295 E.04966
G1 X125.66 Y120.745 E.06149
G3 X128.123 Y120.268 I3.707 J12.55 E.3006
G1 X128.197 Y119.733 E.06467
G1 X128.611 Y119.765 E.04966
G1 X128.601 Y120.279 E.06148
G3 X130.972 Y121.097 I-3.064 J12.72 E.3006
G1 X131.304 Y120.671 E.06467
G1 X131.647 Y120.906 E.04966
G1 X131.381 Y121.346 E.06148
G3 X133.025 Y123.24 I-9.014 J9.485 E.3006
G1 X133.526 Y123.037 E.06468
G1 X133.705 Y123.412 E.04966
G1 X133.255 Y123.66 E.06149
G3 X133.732 Y126.123 I-12.549 J3.707 E.3006
G1 X134.267 Y126.197 E.06467
G1 X134.235 Y126.611 E.04966
G1 X133.721 Y126.601 E.06148
M73 P83 R1
G3 X132.903 Y128.972 I-12.72 J-3.064 E.3006
G1 X133.329 Y129.304 E.06467
G1 X133.094 Y129.647 E.04966
G1 X132.654 Y129.381 E.06148
G3 X130.76 Y131.025 I-9.485 J-9.014 E.3006
G1 X130.963 Y131.526 E.06468
G1 X130.588 Y131.705 E.04966
G1 X130.34 Y131.255 E.06149
G3 X127.877 Y131.732 I-3.707 J-12.549 E.3006
G1 X127.803 Y132.267 E.06467
G1 X127.389 Y132.235 E.04966
G1 X127.399 Y131.721 E.06148
G3 X125.028 Y130.903 I3.064 J-12.721 E.3006
G1 X124.696 Y131.329 E.06467
G1 X124.353 Y131.094 E.04966
G1 X124.619 Y130.654 E.06148
G3 X123.742 Y129.736 I9.014 J-9.485 E.15189
G1 X123.48 Y129.405 E.05054
G1 X122.654 Y129.682 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2420
G3 X120 Y130.339 I-3.132 J-6.965 E.32895
G1 X119.925 Y130.194 E.01947
G3 X119.69 Y129.71 I5.43 J-2.929 E.06442
G3 X121.895 Y127.971 I5.437 J4.625 E.33818
G3 X121.612 Y126.527 I9.267 J-2.563 E.17614
G1 X121.529 Y126.516 E.01002
G3 X118.902 Y125.757 I.772 J-7.602 E.32895
G1 X118.91 Y125.595 E.01947
G3 X118.949 Y125.058 I6.167 J.178 E.06442
G3 X121.727 Y124.654 I2.396 J6.724 E.33818
G3 X122.204 Y123.263 I9.305 J2.413 E.17614
G1 X122.138 Y123.211 E.01002
G3 X120.242 Y121.241 I4.466 J-6.194 E.32895
G1 X120.33 Y121.104 E.01947
G3 X120.632 Y120.659 I5.252 J3.238 E.06442
G3 X123.241 Y121.698 I-1.287 J7.022 E.33818
G3 X124.35 Y120.732 I6.853 J6.743 E.17614
G1 X124.318 Y120.654 E.01002
G3 X123.661 Y118 I6.965 J-3.132 E.32895
G1 X123.806 Y117.925 E.01947
G3 X124.29 Y117.69 I2.929 J5.43 E.06442
G3 X126.029 Y119.895 I-4.625 J5.437 E.33818
G3 X127.473 Y119.612 I2.563 J9.267 E.17614
G1 X127.484 Y119.529 E.01002
G3 X128.243 Y116.904 I7.116 J.634 E.32897
G1 X128.405 Y116.911 E.01938
G3 X128.942 Y116.949 I-.118 J5.511 E.06449
G3 X129.346 Y119.727 I-6.724 J2.396 E.33818
G3 X130.737 Y120.204 I-2.413 J9.305 E.17614
G1 X130.789 Y120.138 E.01002
G3 X132.759 Y118.242 I6.195 J4.466 E.32895
G1 X132.896 Y118.33 E.01947
G3 X133.341 Y118.632 I-3.237 J5.252 E.06442
G3 X132.302 Y121.241 I-7.021 J-1.287 E.33818
G3 X133.268 Y122.35 I-6.743 J6.853 E.17614
G1 X133.346 Y122.318 E.01002
G3 X136 Y121.661 I3.132 J6.965 E.32895
G1 X136.075 Y121.806 E.01947
G3 X136.31 Y122.29 I-5.43 J2.929 E.06442
G3 X134.105 Y124.029 I-5.437 J-4.625 E.33818
G3 X134.388 Y125.473 I-9.266 J2.563 E.17614
G1 X134.471 Y125.484 E.01002
G3 X137.098 Y126.243 I-.772 J7.602 E.32895
G1 X137.09 Y126.405 E.01947
G3 X137.051 Y126.942 I-6.167 J-.178 E.06442
G3 X134.273 Y127.346 I-2.396 J-6.724 E.33818
G3 X133.796 Y128.737 I-9.305 J-2.413 E.17614
G1 X133.862 Y128.789 E.01002
G3 X135.758 Y130.759 I-4.466 J6.195 E.32895
G1 X135.67 Y130.896 E.01947
G3 X135.368 Y131.341 I-5.252 J-3.238 E.06442
G3 X132.759 Y130.302 I1.287 J-7.021 E.33818
G3 X131.65 Y131.268 I-6.853 J-6.743 E.17614
G1 X131.682 Y131.346 E.01002
G3 X132.339 Y134 I-6.965 J3.132 E.32895
G1 X132.194 Y134.075 E.01947
G3 X131.71 Y134.31 I-2.929 J-5.43 E.06442
G3 X129.971 Y132.105 I4.625 J-5.437 E.33818
G3 X128.527 Y132.388 I-2.563 J-9.266 E.17614
G1 X128.516 Y132.471 E.01002
G3 X127.757 Y135.098 I-7.602 J-.772 E.32895
G1 X127.595 Y135.09 E.01947
G3 X127.058 Y135.051 I.178 J-6.167 E.06442
G3 X126.654 Y132.273 I6.724 J-2.396 E.33818
G3 X125.263 Y131.796 I2.413 J-9.305 E.17614
G1 X125.211 Y131.862 E.01002
G3 X123.241 Y133.758 I-6.195 J-4.466 E.32895
G1 X123.104 Y133.67 E.01947
G3 X122.659 Y133.368 I3.238 J-5.252 E.06442
G3 X123.698 Y130.759 I7.021 J1.287 E.33818
G3 X122.753 Y129.679 I6.743 J-6.853 E.1718
M204 S10000
; WIPE_START
G1 F24000
G1 X122.109 Y129.903 E-.97199
G1 X121.445 Y130.116 E-.99373
G1 X120.838 Y130.245 E-.88428
; WIPE_END
G1 E-.15 F1800
G1 X122.053 Y128.934 Z7.2 F30000
G1 Z6.8
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 1.08555
G2 X121.518 Y129.198 I5.121 J11.063 E.09728
; LINE_WIDTH: 1.04714
G1 F1872.461
G1 X121.39 Y129.261 E.02231
; LINE_WIDTH: 0.998278
G1 F1972.738
G1 X121.262 Y129.324 E.02118
; LINE_WIDTH: 0.973846
G1 F2027.015
G1 X120.181 Y129.888 E.17645
G1 X120.178 Y129.881 F30000
; LINE_WIDTH: 0.839532
G1 F2388.247
G1 X122.042 Y128.91 E.25815
G1 X123.447 Y128.201 F30000
; LINE_WIDTH: 0.771751
G1 F2420
G1 X123.419 Y128.129 E.0086
; LINE_WIDTH: 0.741695
G3 X123.329 Y127.852 I5.068 J-1.807 E.03111
; LINE_WIDTH: 0.705854
G1 X123.251 Y127.61 E.02573
; LINE_WIDTH: 0.684741
G3 X122.971 Y125.983 I6.543 J-1.963 E.16152
; LINE_WIDTH: 0.755227
G1 X122.957 Y125.629 E.03861
G1 X122.983 Y125.475 E.01709
; LINE_WIDTH: 0.729642
G3 X123.045 Y125.191 I5.273 J1.009 E.03045
; LINE_WIDTH: 0.698138
G1 X123.101 Y124.943 E.02539
; LINE_WIDTH: 0.678513
G3 X123.258 Y124.393 I34.907 J9.668 E.05525
G1 X123.342 Y124.172 E.02288
; LINE_WIDTH: 0.692805
G3 X123.673 Y123.431 I7.336 J2.837 E.08032
; LINE_WIDTH: 0.726861
G1 X123.689 Y123.4 E.00362
; LINE_WIDTH: 0.757981
G3 X123.97 Y122.977 I1.167 J.472 E.05605
; LINE_WIDTH: 0.718867
G3 X124.167 Y122.765 I4.025 J3.535 E.02985
; LINE_WIDTH: 0.691675
G1 X124.341 Y122.579 E.02512
; LINE_WIDTH: 0.681634
G3 X125.393 Y121.712 I4.222 J4.056 E.13272
; LINE_WIDTH: 0.722539
G1 X125.603 Y121.568 E.0264
; LINE_WIDTH: 0.762934
G3 X125.949 Y121.395 I.821 J1.204 E.04274
; LINE_WIDTH: 0.738322
G1 X126.097 Y121.342 E.01678
; LINE_WIDTH: 0.720846
G1 X126.13 Y121.331 E.00355
; LINE_WIDTH: 0.687083
G3 X127.965 Y120.977 I2.148 J6.206 E.18379
; LINE_WIDTH: 0.733582
G1 X128.219 Y120.96 E.02687
; LINE_WIDTH: 0.764804
G3 X128.565 Y120.994 I.072 J1.037 E.03859
; LINE_WIDTH: 0.729989
G1 X128.759 Y121.031 E.02073
; LINE_WIDTH: 0.683932
G3 X129.828 Y121.338 I-1.566 J7.474 E.10857
G1 X130.295 Y121.54 E.04953
; LINE_WIDTH: 0.708519
G3 X130.552 Y121.668 I-2.24 J4.843 E.02916
; LINE_WIDTH: 0.745867
G1 X130.78 Y121.782 E.02739
; LINE_WIDTH: 0.762802
G3 X131.022 Y121.973 I-.334 J.671 E.03427
; LINE_WIDTH: 0.722312
G1 X131.2 Y122.13 E.02459
; LINE_WIDTH: 0.679959
G3 X131.77 Y122.69 I-32.527 J33.671 E.07744
; LINE_WIDTH: 0.629248
G3 X131.99 Y122.923 I-4.721 J4.67 E.02837
G1 X132.181 Y123.251 E.03357
; LINE_WIDTH: 0.653219
G1 X132.371 Y123.579 E.03505
G1 X133.947 Y123.066 F30000
; LINE_WIDTH: 1.07659
G1 F1816.809
G2 X134.482 Y122.802 I-5.116 J-11.053 E.0964
; LINE_WIDTH: 1.04715
G1 F1872.45
G1 X134.61 Y122.739 E.02231
; LINE_WIDTH: 0.998284
G1 F1972.725
G1 X134.738 Y122.676 E.02118
; LINE_WIDTH: 0.968596
G1 F2039.07
G1 X135.82 Y122.111 E.17559
G1 X135.823 Y122.118 F30000
; LINE_WIDTH: 0.821229
G1 F2420
G1 X133.958 Y123.09 E.25205
G1 X134.69 Y125.885 F30000
; LINE_WIDTH: 1.01338
G1 F1940.617
G1 X134.834 Y126.079 E.03641
; LINE_WIDTH: 1.03388
G1 F1898.648
G1 X134.977 Y126.272 E.03722
; LINE_WIDTH: 1.07489
G1 F1819.929
G1 X135.121 Y126.465 E.03883
; LINE_WIDTH: 1.07192
G1 F1825.412
G2 X135.286 Y126.476 I.303 J-3.355 E.02654
; LINE_WIDTH: 1.03208
G1 F1902.261
G1 X135.376 Y126.481 E.01393
; LINE_WIDTH: 0.996095
G1 F1977.469
G1 X135.497 Y126.49 E.01804
; LINE_WIDTH: 0.970633
G1 F2034.376
G1 X136.715 Y126.55 E.1758
G1 X136.715 Y126.55 F30000
; LINE_WIDTH: 0.821231
G1 F2420
G1 X134.615 Y126.459 E.25189
G1 X132.204 Y126.336 F30000
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.871961
G1 F2289.727
G1 X132.204 Y127.383 E.13415
G1 X132.649 Y127.571 E.06183
G1 X132.998 Y126.364 E.16095
G1 X132.987 Y126.281 E.01078
; LINE_WIDTH: 0.850243
G1 F2354.782
G1 X132.922 Y125.663 E.07735
; LINE_WIDTH: 0.790289
G1 F2420
G1 X132.857 Y125.046 E.07128
G1 X132.66 Y124.24 E.09529
G1 X132.161 Y124.53 E.06628
G1 X132.161 Y125.095 E.06483
; LINE_WIDTH: 0.806807
G1 X132.18 Y125.655 E.0659
; LINE_WIDTH: 0.828525
G1 X132.2 Y126.216 E.06789
G1 X132.402 Y128.292 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 0.765529
G1 F2420
G1 X132.151 Y128.884 E.07125
; LINE_WIDTH: 0.748333
G1 X132.103 Y128.955 E.0092
; LINE_WIDTH: 0.713942
G1 X132.055 Y129.025 E.00872
; LINE_WIDTH: 0.67955
G1 X132.007 Y129.095 E.00824
; LINE_WIDTH: 0.671262
G1 X131.421 Y129.652 E.07717
; LINE_WIDTH: 0.684467
G3 X130.549 Y130.327 I-3.984 J-4.244 E.1077
; LINE_WIDTH: 0.732203
G1 X130.338 Y130.469 E.02681
; LINE_WIDTH: 0.764761
G3 X130.018 Y130.616 I-.605 J-.895 E.0391
; LINE_WIDTH: 0.730954
G1 X129.836 Y130.68 E.02026
; LINE_WIDTH: 0.684067
G3 X128.252 Y131.009 I-2.17 J-6.474 E.15814
; LINE_WIDTH: 0.707499
G3 X127.965 Y131.027 I-.486 J-5.31 E.02911
; LINE_WIDTH: 0.744339
G1 X127.711 Y131.043 E.02733
; LINE_WIDTH: 0.763299
G3 X127.401 Y130.999 I-.048 J-.778 E.03479
; LINE_WIDTH: 0.723193
G1 X127.173 Y130.954 E.02414
; LINE_WIDTH: 0.683279
G3 X125.643 Y130.43 I1.394 J-6.574 E.15788
; LINE_WIDTH: 0.716608
G3 X125.386 Y130.301 I2.277 J-4.836 E.02959
; LINE_WIDTH: 0.757733
G1 X125.159 Y130.185 E.0279
; LINE_WIDTH: 0.754982
G3 X124.94 Y129.992 I1.595 J-2.032 E.03185
; LINE_WIDTH: 0.714805
G1 X124.749 Y129.823 E.02611
; LINE_WIDTH: 0.683282
G3 X123.699 Y128.593 I4.419 J-4.838 E.15786
; LINE_WIDTH: 0.723771
G3 X123.563 Y128.383 I3.835 J-2.622 E.02601
; LINE_WIDTH: 0.762763
G1 X123.447 Y128.201 E.0239
G1 X121.31 Y126.115 F30000
; LINE_WIDTH: 0.99287
G1 F1984.499
G1 X121.166 Y125.921 E.03561
; LINE_WIDTH: 1.03388
G1 F1898.656
G1 X121.023 Y125.728 E.03722
; LINE_WIDTH: 1.07736
G1 F1815.402
G1 X120.879 Y125.535 E.03892
G1 X120.805 Y125.529 E.01209
; LINE_WIDTH: 1.06084
G1 F1846.158
G1 X120.714 Y125.524 E.01435
; LINE_WIDTH: 1.03209
G1 F1902.239
G1 X120.624 Y125.519 E.01393
; LINE_WIDTH: 0.99611
G1 F1977.436
G1 X120.503 Y125.51 E.01804
; LINE_WIDTH: 0.9745
G1 F2025.523
G1 X119.285 Y125.45 E.17657
G1 X119.285 Y125.45 F30000
; LINE_WIDTH: 0.839532
G1 F2388.245
G1 X121.385 Y125.541 E.25816
G1 X122.485 Y122.317 F30000
; LINE_WIDTH: 1.08555
G1 F1800.528
G2 X121.989 Y121.986 I-7.017 J9.961 E.09729
; LINE_WIDTH: 1.04715
G1 F1872.455
G1 X121.871 Y121.906 E.02231
; LINE_WIDTH: 0.998286
G1 F1972.72
M73 P84 R1
G1 X121.752 Y121.827 E.02117
; LINE_WIDTH: 0.973858
G1 F2026.986
G1 X120.723 Y121.173 E.17646
G1 X120.728 Y121.167 F30000
; LINE_WIDTH: 0.839536
G1 F2388.232
G1 X122.501 Y122.295 E.25816
G1 X125.066 Y120.053 F30000
; LINE_WIDTH: 1.08555
G1 F1800.53
G2 X124.802 Y119.518 I-11.047 J5.113 E.09728
; LINE_WIDTH: 1.04714
G1 F1872.461
G1 X124.739 Y119.39 E.02231
; LINE_WIDTH: 0.998279
G1 F1972.736
G1 X124.676 Y119.262 E.02118
; LINE_WIDTH: 0.973848
G1 F2027.011
G1 X124.112 Y118.181 E.17645
G1 X124.119 Y118.178 F30000
; LINE_WIDTH: 0.839543
G1 F2388.212
G1 X125.09 Y120.042 E.25816
G1 X127.885 Y119.31 F30000
; LINE_WIDTH: 1.01337
G1 F1940.633
G1 X128.079 Y119.166 E.03641
; LINE_WIDTH: 1.03388
G1 F1898.66
G1 X128.272 Y119.023 E.03722
; LINE_WIDTH: 1.07489
G1 F1819.934
G1 X128.465 Y118.879 E.03883
; LINE_WIDTH: 1.07254
G1 F1824.273
G2 X128.476 Y118.718 I-3.274 J-.297 E.02591
; LINE_WIDTH: 1.034
G1 F1898.424
G1 X128.481 Y118.632 E.01334
; LINE_WIDTH: 0.996393
G1 F1976.823
G1 X128.588 Y117.286 E.20044
G1 X128.555 Y117.284 F30000
; LINE_WIDTH: 0.840297
G1 F2385.824
G1 X128.451 Y119.384 E.25853
G1 X131.683 Y120.485 F30000
; LINE_WIDTH: 1.07659
G1 F1816.803
G2 X132.014 Y119.989 I-9.96 J-7.016 E.09642
; LINE_WIDTH: 1.04714
G1 F1872.463
G1 X132.094 Y119.871 E.02231
; LINE_WIDTH: 0.99828
G1 F1972.735
G1 X132.173 Y119.752 E.02118
; LINE_WIDTH: 0.968596
G1 F2039.071
G1 X132.828 Y118.722 E.17559
G1 X132.834 Y118.726 F30000
; LINE_WIDTH: 0.821238
G1 F2420
G1 X131.705 Y120.501 E.25206
G1 X133.515 Y129.683 F30000
; LINE_WIDTH: 1.07659
G1 F1816.804
G2 X134.011 Y130.014 I6.999 J-9.933 E.09641
; LINE_WIDTH: 1.04715
G1 F1872.449
G1 X134.129 Y130.094 E.02231
; LINE_WIDTH: 0.998284
G1 F1972.726
G1 X134.248 Y130.173 E.02118
; LINE_WIDTH: 0.968595
G1 F2039.072
G1 X135.277 Y130.827 E.17541
G1 X135.272 Y130.833 F30000
; LINE_WIDTH: 0.821227
G1 F2420
G1 X133.499 Y129.705 E.25189
G1 X130.934 Y131.947 F30000
; LINE_WIDTH: 1.07659
G1 F1816.81
G2 X131.198 Y132.482 I11.073 J-5.126 E.09641
; LINE_WIDTH: 1.04714
G1 F1872.463
G1 X131.261 Y132.61 E.02231
; LINE_WIDTH: 0.998282
G1 F1972.731
G1 X131.324 Y132.738 E.02117
; LINE_WIDTH: 0.9686
G1 F2039.061
G1 X131.888 Y133.819 E.17541
G1 X131.881 Y133.822 F30000
; LINE_WIDTH: 0.821226
G1 F2420
G1 X130.91 Y131.958 E.25188
G1 X128.115 Y132.69 F30000
; LINE_WIDTH: 0.992879
G1 F1984.48
G1 X127.921 Y132.834 E.03561
; LINE_WIDTH: 1.03388
G1 F1898.646
G1 X127.728 Y132.977 E.03722
; LINE_WIDTH: 1.07736
G1 F1815.399
G1 X127.535 Y133.121 E.03892
G1 X127.529 Y133.195 E.01208
; LINE_WIDTH: 1.06084
G1 F1846.156
G1 X127.524 Y133.286 E.01436
; LINE_WIDTH: 1.03208
G1 F1902.263
G1 X127.519 Y133.376 E.01393
; LINE_WIDTH: 0.996094
G1 F1977.471
G1 X127.51 Y133.497 E.01803
; LINE_WIDTH: 0.974484
G1 F2025.56
G1 X127.45 Y134.715 E.17656
G1 X127.45 Y134.715 F30000
; LINE_WIDTH: 0.839537
G1 F2388.229
G1 X127.541 Y132.615 E.25816
G1 X124.317 Y131.515 F30000
; LINE_WIDTH: 1.08555
G1 F1800.524
G2 X123.986 Y132.011 I9.946 J7.007 E.09729
; LINE_WIDTH: 1.04715
G1 F1872.447
G1 X123.906 Y132.129 E.02231
; LINE_WIDTH: 0.998284
G1 F1972.726
G1 X123.827 Y132.248 E.02118
; LINE_WIDTH: 0.973852
G1 F2027.001
G1 X123.173 Y133.277 E.17646
G1 X123.167 Y133.272 F30000
; LINE_WIDTH: 0.839547
G1 F2388.2
G1 X124.295 Y131.499 E.25816
; CHANGE_LAYER
; Z_HEIGHT: 7.2
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X123.221 Y133.187 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 18/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L18
M991 S0 P17 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z7.2 I.945 J.767 P1  F30000
G1 X131.344 Y123.183 Z7.2
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2451.784
G1 X131.444 Y123.276 E.01639
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X128.005 Y121.66 I-2.777 J-3.338 E1.99267
G3 X130.78 Y122.66 I-.013 J4.39 E.35998
G1 X131.256 Y123.101 E.07764
G1 X130.709 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X130.71 Y123.596 E.00008
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X128.01 Y122.395 I-2.307 J-2.773 E1.65625
G1 X128.17 Y122.393 E.01916
G3 X130.312 Y123.223 I-.217 J3.743 E.27931
G1 X130.622 Y123.514 E.05091
M204 S10000
; WIPE_START
G1 F24000
G1 X130.71 Y123.596 E-.17197
G1 X130.71 Y125.476 E-2.67803
; WIPE_END
G1 E-.15 F1800
G1 X124.021 Y129.151 Z7.6 F30000
G1 X123.493 Y129.44 Z7.6
G1 Z7.2
G1 E3 F1800
; FEATURE: Inner wall
G1 F2451.784
G1 X123.041 Y128.904 E.08404
G1 X122.469 Y129.155 E.07473
G1 X122.277 Y128.792 E.04904
G1 X122.807 Y128.462 E.0747
G3 X122.251 Y126.023 I13.312 J-4.316 E.29967
G1 X121.679 Y125.968 E.06873
G1 X121.692 Y125.555 E.04936
G1 X122.272 Y125.535 E.06938
G3 X123.006 Y123.157 I13.632 J2.904 E.29824
G1 X122.502 Y122.787 E.07473
G1 X122.721 Y122.44 E.04904
G1 X123.272 Y122.734 E.07469
G3 X125.096 Y121.041 I10.355 J9.332 E.29824
G1 X124.845 Y120.469 E.07473
G1 X125.208 Y120.277 E.04904
G1 X125.538 Y120.807 E.07469
G3 X127.977 Y120.251 I4.316 J13.311 E.29967
G1 X128.032 Y119.679 E.06874
G1 X128.445 Y119.692 E.04936
G1 X128.465 Y120.272 E.06939
G3 X130.843 Y121.006 I-2.904 J13.633 E.29824
G1 X131.213 Y120.502 E.07473
G1 X131.56 Y120.721 E.04904
G1 X131.266 Y121.272 E.0747
G3 X132.959 Y123.096 I-9.331 J10.354 E.29824
G1 X133.531 Y122.845 E.07473
G1 X133.723 Y123.208 E.04904
G1 X133.193 Y123.538 E.07469
G3 X133.749 Y125.977 I-13.312 J4.316 E.29967
G1 X134.321 Y126.032 E.06874
G1 X134.308 Y126.445 E.04936
G1 X133.728 Y126.465 E.06939
G3 X132.994 Y128.843 I-13.634 J-2.904 E.29824
G1 X133.498 Y129.213 E.07473
G1 X133.279 Y129.56 E.04904
G1 X132.728 Y129.266 E.07469
G3 X130.904 Y130.959 I-10.354 J-9.331 E.29824
G1 X131.155 Y131.531 E.07473
G1 X130.792 Y131.723 E.04904
G1 X130.462 Y131.193 E.0747
G3 X128.023 Y131.749 I-4.316 J-13.312 E.29967
G1 X127.968 Y132.321 E.06874
G1 X127.555 Y132.308 E.04936
G1 X127.535 Y131.728 E.06939
G3 X125.157 Y130.994 I2.904 J-13.633 E.29824
G1 X124.787 Y131.498 E.07473
G1 X124.44 Y131.279 E.04904
G1 X124.734 Y130.728 E.07469
G3 X123.846 Y129.853 I9.333 J-10.356 E.14922
G1 X123.571 Y129.532 E.05056
G1 X122.764 Y129.827 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G3 X120.125 Y130.558 I-3.314 J-6.829 E.32956
G1 X120.044 Y130.418 E.01941
G3 X119.796 Y129.937 I10.234 J-5.594 E.06473
G3 X121.95 Y128.131 I5.947 J4.906 E.33823
G3 X121.624 Y126.7 I9.354 J-2.885 E.17582
G1 X121.552 Y126.693 E.00857
G3 X118.901 Y126.01 I.402 J-7.05 E.3297
G1 X118.901 Y125.848 E.01941
G3 X118.926 Y125.307 I11.659 J.272 E.06473
G3 X121.695 Y124.821 I2.697 J7.222 E.33823
G3 X122.126 Y123.422 I9.526 J2.174 E.17531
G1 X122.068 Y123.379 E.00862
G3 X120.115 Y121.459 I4.257 J-6.285 E.32956
G1 X120.196 Y121.319 E.01941
G3 X120.488 Y120.863 I9.959 J6.064 E.06473
G3 X123.129 Y121.826 I-1.275 J7.603 E.33823
G3 X124.202 Y120.83 I7.164 J6.646 E.17531
G1 X124.173 Y120.764 E.00862
G3 X123.442 Y118.125 I6.829 J-3.314 E.32956
G1 X123.582 Y118.044 E.01941
G3 X124.063 Y117.796 I5.594 J10.234 E.06473
G3 X125.869 Y119.95 I-4.906 J5.947 E.33823
G3 X127.3 Y119.624 I2.885 J9.354 E.17582
G1 X127.307 Y119.552 E.00857
G3 X127.99 Y116.901 I7.087 J.41 E.32967
G1 X128.154 Y116.901 E.01966
G3 X128.693 Y116.926 I-.284 J11.821 E.06453
G3 X129.179 Y119.695 I-7.222 J2.697 E.33823
G3 X130.578 Y120.126 I-2.174 J9.527 E.17531
G1 X130.621 Y120.068 E.00862
G3 X132.541 Y118.115 I6.285 J4.257 E.32956
G1 X132.681 Y118.196 E.01941
G3 X133.137 Y118.488 I-6.065 J9.96 E.06473
G3 X132.174 Y121.129 I-7.603 J-1.275 E.33823
G3 X133.17 Y122.202 I-6.646 J7.164 E.17531
G1 X133.236 Y122.173 E.00862
G3 X135.875 Y121.442 I3.314 J6.829 E.32956
G1 X135.956 Y121.582 E.01941
G3 X136.204 Y122.063 I-10.23 J5.592 E.06473
G3 X134.05 Y123.869 I-5.947 J-4.906 E.33823
G3 X134.377 Y125.3 I-9.354 J2.885 E.17582
G1 X134.448 Y125.307 E.00857
G3 X137.099 Y125.99 I-.402 J7.05 E.3297
G1 X137.099 Y126.152 E.01941
G3 X137.074 Y126.693 I-11.658 J-.272 E.06473
G3 X134.305 Y127.179 I-2.697 J-7.222 E.33823
G3 X133.874 Y128.578 I-9.527 J-2.174 E.17531
G1 X133.932 Y128.621 E.00862
G3 X135.885 Y130.541 I-4.257 J6.285 E.32956
G1 X135.804 Y130.681 E.01941
G3 X135.512 Y131.137 I-9.959 J-6.064 E.06473
G3 X132.871 Y130.174 I1.275 J-7.603 E.33823
G3 X131.798 Y131.17 I-7.164 J-6.646 E.17531
G1 X131.827 Y131.236 E.00862
G3 X132.558 Y133.875 I-6.829 J3.314 E.32956
G1 X132.418 Y133.956 E.01941
G3 X131.937 Y134.204 I-5.593 J-10.232 E.06473
G3 X130.131 Y132.05 I4.906 J-5.947 E.33823
G3 X128.7 Y132.377 I-2.885 J-9.354 E.17582
G1 X128.693 Y132.448 E.00857
G3 X128.01 Y135.099 I-7.05 J-.402 E.3297
G1 X127.848 Y135.099 E.01941
G3 X127.307 Y135.074 I.272 J-11.658 E.06473
G3 X126.821 Y132.305 I7.222 J-2.697 E.33823
G3 X125.422 Y131.874 I2.174 J-9.527 E.17531
G1 X125.379 Y131.932 E.00862
G3 X123.459 Y133.885 I-6.285 J-4.257 E.32956
G1 X123.319 Y133.804 E.01941
G3 X122.863 Y133.512 I6.063 J-9.958 E.06473
G3 X123.826 Y130.871 I7.603 J1.275 E.33823
G3 X122.86 Y129.835 I6.647 J-7.164 E.16957
M204 S10000
; WIPE_START
G1 F24000
G1 X122.219 Y130.066 E-.97175
G1 X121.561 Y130.297 E-.99383
G1 X120.957 Y130.443 E-.88442
; WIPE_END
G1 E-.15 F1800
G1 X122.037 Y129.123 Z7.6 F30000
G1 Z7.2
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 0.8399
G1 F2387.079
G1 X120.288 Y130.097 E.24601
G1 X120.285 Y130.091 F30000
; LINE_WIDTH: 0.666949
G1 F3000
G1 X122.033 Y129.116 E.18958
G1 X121.608 Y129.378 F30000
; LINE_WIDTH: 1.06196
G1 F1844.043
G1 X121.763 Y128.68 E.11364
G1 X121.608 Y129.378 F30000
; LINE_WIDTH: 1.04756
G1 F1871.656
M73 P85 R1
G1 X121.482 Y129.444 E.02232
; LINE_WIDTH: 0.998687
G1 F1971.855
G1 X121.356 Y129.51 E.02119
; LINE_WIDTH: 0.974252
G1 F2026.089
G1 X120.292 Y130.104 E.17647
G1 X123.479 Y128.243 F30000
; LINE_WIDTH: 0.750249
G1 F2709.177
G1 X123.431 Y128.123 E.01403
; LINE_WIDTH: 0.720399
G1 F2836.619
G3 X123.337 Y127.849 I5.021 J-1.875 E.02993
; LINE_WIDTH: 0.692894
G1 F2965.142
G1 X123.255 Y127.608 E.02517
; LINE_WIDTH: 0.68342
G1 F3000
G3 X122.986 Y126.271 I5.7 J-1.842 E.13315
; LINE_WIDTH: 0.73013
G1 F2793.776
G1 X122.957 Y126.018 E.02672
; LINE_WIDTH: 0.769918
G1 F2631.28
G3 X122.97 Y125.643 I1.274 J-.146 E.04197
; LINE_WIDTH: 0.741125
G1 F2746.898
G1 X122.995 Y125.475 E.01808
; LINE_WIDTH: 0.722423
G1 F2827.602
G1 X123.001 Y125.442 E.00357
; LINE_WIDTH: 0.687494
G1 F2991.757
G3 X123.248 Y124.423 I8.654 J1.556 E.10282
G1 X123.266 Y124.371 E.00543
; LINE_WIDTH: 0.691063
G1 F2974.114
G3 X123.554 Y123.655 I7.093 J2.446 E.07613
; LINE_WIDTH: 0.742043
G1 F2743.055
G1 X123.658 Y123.423 E.02723
; LINE_WIDTH: 0.770896
G1 F2627.524
G3 X123.847 Y123.145 I.843 J.372 E.03774
; LINE_WIDTH: 0.732652
G1 F2782.883
G1 X123.979 Y122.983 E.02203
; LINE_WIDTH: 0.685305
G1 F3000
G3 X125.153 Y121.868 I5.34 J4.45 E.15848
; LINE_WIDTH: 0.714864
G1 F2861.581
G3 X125.386 Y121.7 I3.237 J4.251 E.0295
; LINE_WIDTH: 0.755214
G1 F2689.081
G1 X125.594 Y121.552 E.02779
; LINE_WIDTH: 0.767369
G1 F2641.125
G1 X125.868 Y121.437 E.03305
; LINE_WIDTH: 0.72481
G1 F2817.035
G1 X126.101 Y121.35 E.0259
; LINE_WIDTH: 0.68479
G1 F3000
G3 X127.678 Y120.989 I2.314 J6.471 E.1583
; LINE_WIDTH: 0.723781
G1 F2821.579
G3 X127.951 Y120.963 I.606 J5.045 E.02845
; LINE_WIDTH: 0.766001
G1 F2646.433
G1 X128.19 Y120.942 E.02663
; LINE_WIDTH: 0.782056
G1 F2585.408
G1 X128.219 Y120.946 E.00335
; LINE_WIDTH: 0.755145
G1 F2689.359
G3 X128.507 Y120.995 I-.772 J5.346 E.03186
; LINE_WIDTH: 0.715155
G1 F2860.256
G1 X128.758 Y121.039 E.02613
; LINE_WIDTH: 0.685713
G1 F3000
G3 X130.33 Y121.544 I-1.347 J6.894 E.16181
; LINE_WIDTH: 0.757458
G1 F2680.096
G1 X130.693 Y121.716 E.04391
G1 X130.78 Y121.782 E.01197
; LINE_WIDTH: 0.741894
G1 F2743.678
G3 X131.002 Y121.97 I-3.364 J4.203 E.03112
; LINE_WIDTH: 0.706257
G1 F2901.28
G1 X131.196 Y122.135 E.02574
; LINE_WIDTH: 0.675952
G1 F3000
G3 X131.787 Y122.707 I-21.628 J22.964 E.07912
; LINE_WIDTH: 0.632522
G1 X131.991 Y122.922 E.02641
G1 X132.209 Y123.28 E.03731
; LINE_WIDTH: 0.665202
G1 X132.427 Y123.637 E.03954
G1 X133.963 Y122.877 F30000
; LINE_WIDTH: 0.821609
G1 F2446.422
G1 X135.712 Y121.903 E.24004
G1 X135.715 Y121.909 F30000
; LINE_WIDTH: 0.650402
G1 F3000
G1 X133.967 Y122.884 E.18418
G1 X134.392 Y122.622 F30000
; LINE_WIDTH: 1.07325
G1 F1822.95
G1 X134.237 Y123.32 E.11495
G1 X134.392 Y122.622 F30000
; LINE_WIDTH: 1.04756
G1 F1871.647
G1 X134.518 Y122.556 E.02232
; LINE_WIDTH: 0.99869
G1 F1971.848
G1 X134.644 Y122.49 E.02119
; LINE_WIDTH: 0.968996
G1 F2038.147
G1 X135.708 Y121.896 E.17543
; WIPE_START
G1 F24000
G1 X134.644 Y122.49 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X132.061 Y120.56 Z7.6 F30000
G1 Z7.2
G1 E3 F1800
; LINE_WIDTH: 1.07324
G1 F1822.968
G1 X131.847 Y119.879 E.11495
; LINE_WIDTH: 1.04755
G1 F1871.666
G1 X131.923 Y119.758 E.02232
; LINE_WIDTH: 0.998682
G1 F1971.865
G1 X131.999 Y119.638 E.02119
; LINE_WIDTH: 0.968992
G1 F2038.155
G1 X132.624 Y118.592 E.17542
G1 X132.63 Y118.596 F30000
; LINE_WIDTH: 0.821595
G1 F2446.47
G1 X131.603 Y120.314 E.24003
G1 X131.609 Y120.318 F30000
; LINE_WIDTH: 0.650419
G1 F3000
G1 X132.636 Y118.599 E.18418
; WIPE_START
G1 F24000
G1 X131.61 Y120.316 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X128.278 Y118.589 Z7.6 F30000
G1 Z7.2
G1 E3 F1800
; LINE_WIDTH: 1.02451
G1 F1917.605
G1 X128.274 Y118.686 E.01494
; LINE_WIDTH: 1.05802
G1 F1851.504
G1 X128.27 Y118.784 E.01547
; LINE_WIDTH: 1.08103
G1 F1808.706
G3 X128.247 Y119.319 I-10.877 J-.216 E.08687
G1 X128.278 Y118.589 F30000
; LINE_WIDTH: 0.97673
G1 F2020.453
G2 X128.3 Y117.272 I-26.922 J-1.107 E.19115
; WIPE_START
G1 F24000
G1 X128.278 Y118.589 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X125.32 Y119.763 Z7.6 F30000
G1 Z7.2
G1 E3 F1800
; LINE_WIDTH: 1.06199
G1 F1843.983
G1 X124.622 Y119.608 E.11364
; LINE_WIDTH: 1.04756
G1 F1871.652
G1 X124.556 Y119.482 E.02232
; LINE_WIDTH: 0.998688
G1 F1971.853
G1 X124.49 Y119.356 E.02119
; LINE_WIDTH: 0.97425
G1 F2026.092
G1 X123.896 Y118.292 E.17647
G1 X123.903 Y118.288 F30000
; LINE_WIDTH: 0.839904
G1 F2387.067
G1 X124.877 Y120.037 E.24601
G1 X124.884 Y120.033 F30000
; LINE_WIDTH: 0.666947
G1 F3000
G1 X123.909 Y118.285 E.18958
; WIPE_START
G1 F24000
G1 X124.883 Y120.032 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X122.56 Y121.939 Z7.6 F30000
G1 Z7.2
G1 E3 F1800
; LINE_WIDTH: 1.06198
G1 F1844.004
G1 X121.879 Y122.153 E.11364
; LINE_WIDTH: 1.04755
G1 F1871.662
G1 X121.758 Y122.077 E.02232
; LINE_WIDTH: 0.998685
G1 F1971.859
G1 X121.638 Y122.001 E.02119
; LINE_WIDTH: 0.974252
G1 F2026.089
G1 X120.592 Y121.376 E.17647
G1 X120.596 Y121.37 F30000
; LINE_WIDTH: 0.839894
G1 F2387.099
G1 X122.314 Y122.397 E.24601
G1 X122.318 Y122.391 F30000
; LINE_WIDTH: 0.666941
G1 F3000
G1 X120.599 Y121.364 E.18958
; WIPE_START
G1 F24000
G1 X122.316 Y122.39 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X120.62 Y125.724 Z7.6 F30000
G1 Z7.2
G1 E3 F1800
; LINE_WIDTH: 1.0344
G1 F1897.618
G1 X120.707 Y125.726 E.01335
; LINE_WIDTH: 1.06189
G1 F1844.173
G1 X120.793 Y125.729 E.01374
; LINE_WIDTH: 1.07935
G1 F1811.759
G1 X121.319 Y125.756 E.08521
G1 X121.319 Y125.731 F30000
; LINE_WIDTH: 0.840681
G1 F2384.61
G1 X119.273 Y125.687 E.25183
G1 X119.273 Y125.686 F30000
; LINE_WIDTH: 0.666935
G1 F3000
G1 X121.32 Y125.716 E.19388
G1 X120.62 Y125.724 F30000
; LINE_WIDTH: 1.02065
G1 F1925.523
G1 X119.274 Y125.654 E.20534
G1 X123.479 Y128.243 F30000
; LINE_WIDTH: 0.768728
G1 F2635.868
G2 X123.667 Y128.573 I.869 J-.278 E.04254
; LINE_WIDTH: 0.735209
G1 F2771.924
G1 X123.687 Y128.601 E.00372
; LINE_WIDTH: 0.719468
G1 F2840.788
G1 X123.84 Y128.805 E.02627
; LINE_WIDTH: 0.682153
G1 F3000
G2 X124.753 Y129.818 I4.837 J-3.436 E.13286
; LINE_WIDTH: 0.699453
G1 F2933.448
G1 X124.945 Y129.985 E.02545
; LINE_WIDTH: 0.731276
G1 F2788.817
G2 X125.166 Y130.174 I3.608 J-3.984 E.03053
; LINE_WIDTH: 0.76227
G1 F2661.033
G2 X125.606 Y130.427 I.817 J-.91 E.05644
; LINE_WIDTH: 0.690915
G1 F2974.839
G2 X126.524 Y130.783 I3.389 J-7.382 E.09709
; LINE_WIDTH: 0.686887
G1 F2994.78
G1 X126.648 Y130.821 E.01277
G2 X127.391 Y130.986 I1.948 J-7.009 E.07453
; LINE_WIDTH: 0.741113
G1 F2746.951
G2 X127.711 Y131.044 I1.225 J-5.898 E.03479
; LINE_WIDTH: 0.756577
G1 F2683.616
G1 X127.81 Y131.057 E.01092
G1 X128.219 Y131.023 E.04488
; LINE_WIDTH: 0.685605
G1 F3000
G2 X129.833 Y130.672 I-.676 J-7 E.16178
; LINE_WIDTH: 0.716297
G1 F2855.077
G1 X130.072 Y130.585 E.02618
; LINE_WIDTH: 0.756807
G1 F2682.698
G2 X130.346 Y130.483 I-1.735 J-5.116 E.03195
; LINE_WIDTH: 0.782822
G1 F2582.567
G1 X130.365 Y130.475 E.00228
; LINE_WIDTH: 0.765429
G1 F2648.664
G1 X130.565 Y130.334 E.02713
; LINE_WIDTH: 0.722918
G1 F2825.404
G2 X130.792 Y130.173 I-2.877 J-4.295 E.0289
; LINE_WIDTH: 0.683648
G1 F3000
G2 X131.52 Y129.559 I-3.949 J-5.418 E.09294
; LINE_WIDTH: 0.66118
G1 X132.001 Y129.089 E.06304
; LINE_WIDTH: 0.666439
G1 X132.257 Y128.701 E.04395
; LINE_WIDTH: 0.689257
G1 F2983.015
G1 X132.512 Y128.313 E.04568
G1 X132.208 Y127.31 F30000
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.879413
G1 F2268.225
G1 X132.339 Y127.284 E.01725
G1 X132.667 Y127.5 E.05085
G1 X132.989 Y126.272 E.16419
G1 X132.995 Y126.103 E.02186
G1 X132.784 Y124.923 E.15503
G1 X132.64 Y124.402 E.06997
G1 X132.208 Y124.687 E.067
G1 X132.208 Y127.19 E.32367
G1 X134.68 Y126.284 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 0.65043
G1 F3000
G1 X136.727 Y126.314 E.18836
G1 X136.727 Y126.313 F30000
; LINE_WIDTH: 0.825545
G1 F2433.405
G1 X134.681 Y126.269 E.24677
G1 X134.681 Y126.244 F30000
; LINE_WIDTH: 1.07176
G1 F1825.707
G2 X135.293 Y126.274 I.903 J-12.484 E.09843
; LINE_WIDTH: 1.03439
G1 F1897.625
G1 X135.38 Y126.276 E.01335
; LINE_WIDTH: 0.996782
G1 F1975.978
G1 X136.726 Y126.346 E.2001
; WIPE_START
G1 F24000
G1 X135.38 Y126.276 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X134.362 Y129.999 Z7.6 F30000
G1 Z7.2
G1 E3 F1800
; LINE_WIDTH: 0.968996
G1 F2038.146
G1 X135.408 Y130.624 E.17543
G1 X135.404 Y130.63 F30000
; LINE_WIDTH: 0.821601
G1 F2446.45
G1 X133.686 Y129.603 E.24004
G1 X133.682 Y129.609 F30000
; LINE_WIDTH: 0.650418
G1 F3000
G1 X135.401 Y130.636 E.18419
G1 X134.362 Y129.999 F30000
; LINE_WIDTH: 0.998689
G1 F1971.85
G1 X134.242 Y129.923 E.02119
; LINE_WIDTH: 1.04756
G1 F1871.652
G1 X134.121 Y129.847 E.02232
; LINE_WIDTH: 1.07325
G1 F1822.953
G1 X133.44 Y130.061 E.11496
G1 X131.123 Y131.963 F30000
; LINE_WIDTH: 0.821602
G1 F2446.446
G1 X132.097 Y133.712 E.24004
G1 X132.091 Y133.715 F30000
; LINE_WIDTH: 0.6504
G1 F3000
G1 X131.116 Y131.967 E.18418
G1 X131.378 Y132.392 F30000
; LINE_WIDTH: 1.04755
G1 F1871.659
G1 X131.444 Y132.518 E.02232
; LINE_WIDTH: 0.998682
G1 F1971.864
G1 X131.51 Y132.644 E.02119
; LINE_WIDTH: 0.968995
G1 F2038.148
G1 X132.104 Y133.708 E.17542
G1 X131.378 Y132.392 F30000
; LINE_WIDTH: 1.07324
G1 F1822.968
G1 X130.68 Y132.237 E.11495
G1 X127.756 Y132.681 F30000
; LINE_WIDTH: 1.07934
G1 F1811.769
G1 X127.729 Y133.207 E.0852
; LINE_WIDTH: 1.06189
G1 F1844.174
G1 X127.726 Y133.293 E.01374
; LINE_WIDTH: 1.0344
G1 F1897.62
G1 X127.724 Y133.38 E.01335
; LINE_WIDTH: 1.02065
G1 F1925.524
G1 X127.654 Y134.726 E.20534
G1 X127.686 Y134.727 F30000
; LINE_WIDTH: 0.666929
G1 F3000
G1 X127.716 Y132.68 E.19387
G1 X127.731 Y132.681 F30000
; LINE_WIDTH: 0.840663
G1 F2384.669
G1 X127.687 Y134.727 E.25182
; WIPE_START
G1 F24000
G1 X127.73 Y132.728 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X124.001 Y132.362 Z7.6 F30000
G1 Z7.2
G1 E3 F1800
; LINE_WIDTH: 0.974251
G1 F2026.092
G1 X123.376 Y133.408 E.17647
G1 X123.37 Y133.404 F30000
; LINE_WIDTH: 0.839895
G1 F2387.095
G1 X124.397 Y131.686 E.24601
G1 X124.391 Y131.682 F30000
; LINE_WIDTH: 0.66695
G1 F3000
G1 X123.364 Y133.401 E.18958
G1 X124.001 Y132.362 F30000
; LINE_WIDTH: 0.998685
G1 F1971.859
G1 X124.077 Y132.242 E.02119
; LINE_WIDTH: 1.04755
G1 F1871.661
G1 X124.153 Y132.121 E.02232
; LINE_WIDTH: 1.06198
G1 F1844
G1 X123.939 Y131.44 E.11364
; CHANGE_LAYER
; Z_HEIGHT: 7.6
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X124.153 Y132.121 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 19/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L19
M991 S0 P18 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z7.6 I.948 J.763 P1  F30000
G1 X131.344 Y123.183 Z7.6
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2451.784
G1 X131.444 Y123.276 E.0164
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X127.977 Y121.661 I-2.777 J-3.338 E1.98935
G3 X130.78 Y122.66 I.015 J4.389 E.36328
G1 X131.256 Y123.101 E.07763
G1 X130.71 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X127.982 Y122.395 I-2.307 J-2.773 E1.65293
G1 X128.17 Y122.393 E.02246
G3 X130.627 Y123.509 I-.217 J3.743 E.33037
M204 S10000
; WIPE_START
G1 F24000
G1 X130.661 Y125.509 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X124.04 Y129.306 Z8 F30000
G1 X123.589 Y129.564 Z8
G1 Z7.6
G1 E3 F1800
; FEATURE: Inner wall
G1 F2451.784
G1 X123.12 Y129.042 E.08395
G1 X122.554 Y129.309 E.07484
G1 X122.353 Y128.952 E.049
G1 X122.874 Y128.607 E.07477
G3 X122.253 Y126.195 I14.338 J-4.979 E.29832
G1 X121.669 Y126.146 E.07005
G1 X121.676 Y125.734 E.04931
G1 X122.255 Y125.705 E.06933
G3 X122.925 Y123.295 I14.963 J2.863 E.29967
G1 X122.411 Y122.939 E.07483
G1 X122.62 Y122.586 E.049
G1 X123.179 Y122.864 E.07477
G3 X124.958 Y121.12 I11.478 J9.925 E.29834
G1 X124.691 Y120.554 E.07484
G1 X125.048 Y120.353 E.049
G1 X125.393 Y120.874 E.07478
G3 X127.805 Y120.253 I4.979 J14.338 E.29832
G1 X127.857 Y119.629 E.07489
G1 X128.266 Y119.633 E.049
G1 X128.306 Y120.257 E.07482
G3 X130.705 Y120.925 I-2.857 J14.907 E.29833
G1 X131.061 Y120.411 E.07485
G1 X131.414 Y120.62 E.049
G1 X131.136 Y121.179 E.07479
G3 X132.88 Y122.958 I-9.925 J11.478 E.29833
G1 X133.446 Y122.691 E.07487
G1 X133.647 Y123.047 E.049
G1 X133.126 Y123.393 E.0748
G3 X133.747 Y125.805 I-14.338 J4.979 E.29833
M73 P86 R1
G1 X134.33 Y125.854 E.07
G1 X134.324 Y126.266 E.04931
G1 X133.745 Y126.295 E.06929
G3 X133.075 Y128.705 I-14.962 J-2.863 E.29967
G1 X133.589 Y129.061 E.07485
G1 X133.38 Y129.414 E.049
G1 X132.821 Y129.136 E.07479
G3 X131.042 Y130.88 I-11.48 J-9.927 E.29833
G1 X131.309 Y131.446 E.07484
G1 X130.952 Y131.647 E.049
G1 X130.607 Y131.126 E.07478
G3 X128.195 Y131.747 I-4.979 J-14.337 E.29833
G1 X128.146 Y132.33 E.07
G1 X127.734 Y132.324 E.04931
G1 X127.705 Y131.745 E.06929
G3 X125.295 Y131.075 I2.863 J-14.962 E.29967
G1 X124.939 Y131.589 E.07483
G1 X124.586 Y131.38 E.049
G1 X124.864 Y130.821 E.07477
G3 X123.955 Y129.967 I9.926 J-11.48 E.14931
G1 X123.67 Y129.653 E.05068
G1 X122.87 Y129.972 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G3 X120.253 Y130.775 I-3.504 J-6.752 E.32932
G3 X120.17 Y130.637 I1.544 J-1.03 E.01936
G3 X119.91 Y130.163 I4.637 J-2.846 E.06462
G3 X122.01 Y128.299 I6.055 J4.705 E.33784
G3 X121.645 Y126.881 I10.089 J-3.355 E.17534
G1 X121.572 Y126.875 E.00878
G3 X118.904 Y126.262 I.342 J-7.6 E.32932
G3 X118.9 Y126.1 I1.852 J-.12 E.01936
G3 X118.913 Y125.561 I5.44 J-.146 E.06462
G3 X121.662 Y125 I2.789 J6.654 E.33789
G3 X122.056 Y123.585 I10.432 J2.141 E.17582
G1 X121.995 Y123.544 E.00878
G3 X119.991 Y121.679 I4.096 J-6.411 E.32932
G3 X120.069 Y121.537 I1.664 J.822 E.01936
G3 X120.35 Y121.076 I4.784 J2.593 E.06462
G3 X123.014 Y121.962 I-1.047 J7.595 E.33784
G3 X124.059 Y120.937 I7.948 J7.058 E.17535
G1 X124.028 Y120.87 E.00878
G3 X123.225 Y118.253 I6.752 J-3.504 E.32932
G3 X123.363 Y118.17 I1.03 J1.544 E.01936
G3 X123.837 Y117.91 I2.847 J4.638 E.06462
G3 X125.701 Y120.01 I-4.705 J6.055 E.33784
G3 X127.119 Y119.645 I3.355 J10.089 E.17534
G1 X127.125 Y119.572 E.00878
G3 X127.737 Y116.904 I7.621 J.345 E.32929
G3 X127.9 Y116.9 I.122 J1.884 E.01951
G1 X128.041 Y116.901 E.01687
G3 X128.439 Y116.913 I.077 J4.054 E.04767
G3 X129.004 Y119.663 I-7.102 J2.891 E.33784
G3 X130.415 Y120.056 I-2.139 J10.415 E.17534
G1 X130.456 Y119.995 E.00878
G3 X132.321 Y117.991 I6.411 J4.096 E.32932
G3 X132.463 Y118.069 I-.822 J1.664 E.01936
G3 X132.924 Y118.35 I-2.593 J4.784 E.06462
G3 X132.038 Y121.014 I-7.596 J-1.048 E.33784
G3 X133.063 Y122.059 I-7.058 J7.948 E.17534
G1 X133.13 Y122.028 E.00878
G3 X135.747 Y121.225 I3.504 J6.752 E.32932
G3 X135.83 Y121.363 I-1.544 J1.03 E.01936
G3 X136.09 Y121.837 I-4.637 J2.846 E.06462
G3 X133.99 Y123.701 I-6.055 J-4.705 E.33784
G3 X134.355 Y125.119 I-10.089 J3.355 E.17534
G1 X134.428 Y125.125 E.00878
G3 X137.096 Y125.738 I-.342 J7.6 E.32932
G3 X137.1 Y125.9 I-1.852 J.12 E.01936
G3 X137.087 Y126.439 I-5.44 J.146 E.06462
G3 X134.338 Y127 I-2.789 J-6.654 E.33789
G3 X133.944 Y128.415 I-10.432 J-2.141 E.17582
G1 X134.005 Y128.456 E.00878
G3 X136.009 Y130.321 I-4.096 J6.411 E.32932
G3 X135.931 Y130.463 I-1.664 J-.822 E.01936
G3 X135.65 Y130.924 I-4.783 J-2.592 E.06462
G3 X132.986 Y130.038 I1.048 J-7.596 E.33784
G3 X131.941 Y131.063 I-7.949 J-7.06 E.17534
G1 X131.972 Y131.13 E.00878
G3 X132.775 Y133.747 I-6.752 J3.504 E.32932
G3 X132.637 Y133.83 I-1.03 J-1.544 E.01936
G3 X132.163 Y134.09 I-2.847 J-4.638 E.06462
G3 X130.299 Y131.99 I4.705 J-6.055 E.33785
G3 X128.881 Y132.355 I-3.355 J-10.089 E.17534
G1 X128.875 Y132.428 E.00878
G3 X128.262 Y135.096 I-7.6 J-.342 E.32932
G3 X128.1 Y135.1 I-.12 J-1.851 E.01936
G3 X127.561 Y135.087 I-.146 J-5.44 E.06462
G3 X127 Y132.338 I6.654 J-2.789 E.33789
G3 X125.585 Y131.944 I2.14 J-10.432 E.17582
G1 X125.544 Y132.005 E.00878
G3 X123.679 Y134.009 I-6.411 J-4.096 E.32932
G3 X123.537 Y133.931 I.822 J-1.664 E.01936
G3 X123.076 Y133.65 I2.593 J-4.784 E.06462
G3 X123.962 Y130.986 I7.595 J1.047 E.33784
G3 X122.967 Y129.976 I7.059 J-7.949 E.16977
M204 S10000
; WIPE_START
G1 F24000
G1 X122.335 Y130.224 E-.96819
G1 X121.683 Y130.473 E-.99404
G1 X121.082 Y130.637 E-.88777
; WIPE_END
G1 E-.15 F1800
G1 X122.135 Y129.312 Z8 F30000
G1 Z7.6
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 1.04723
G1 F1872.3
G1 X121.796 Y129.503 E.06091
; LINE_WIDTH: 0.998392
G1 F1972.492
G1 X121.457 Y129.693 E.05782
; LINE_WIDTH: 0.973976
G1 F2026.718
G1 X120.409 Y130.316 E.17646
G1 X122.122 Y129.29 F30000
; LINE_WIDTH: 0.839653
G1 F2387.862
G1 X120.405 Y130.31 E.24532
G1 X120.402 Y130.304 F30000
; LINE_WIDTH: 0.666701
G1 F3000
G1 X122.118 Y129.283 E.18904
G1 X121.306 Y125.93 F30000
; LINE_WIDTH: 1.07526
G1 F1819.255
G1 X120.772 Y125.931 E.08613
; LINE_WIDTH: 1.04908
G1 F1868.687
G1 X120.639 Y125.927 E.02088
; LINE_WIDTH: 1.01146
G1 F1944.643
G1 X119.953 Y125.928 E.10339
; LINE_WIDTH: 0.995052
G1 F1979.738
G1 X119.268 Y125.928 E.10155
; WIPE_START
G1 F24000
G1 X119.953 Y125.928 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X120.467 Y121.584 Z8 F30000
G1 Z7.6
G1 E3 F1800
; LINE_WIDTH: 0.973985
G1 F2026.697
G1 X121.53 Y122.18 E.17646
; LINE_WIDTH: 0.998404
G1 F1972.465
G1 X121.865 Y122.378 E.05782
; LINE_WIDTH: 1.04724
G1 F1872.272
G1 X122.199 Y122.576 E.06092
G1 X122.212 Y122.554 F30000
; LINE_WIDTH: 0.839652
G1 F2387.864
G1 X120.47 Y121.578 E.24533
G1 X120.474 Y121.572 F30000
; LINE_WIDTH: 0.666678
G1 F3000
G1 X122.216 Y122.548 E.18904
; WIPE_START
G1 F24000
G1 X120.474 Y121.572 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.684 Y118.409 Z8 F30000
G1 Z7.6
G1 E3 F1800
; LINE_WIDTH: 0.973973
G1 F2026.726
G1 X124.307 Y119.457 E.17645
; LINE_WIDTH: 0.998386
G1 F1972.504
G1 X124.497 Y119.796 E.05782
; LINE_WIDTH: 1.04722
G1 F1872.315
G1 X124.688 Y120.135 E.06091
G1 X124.71 Y120.122 F30000
; LINE_WIDTH: 0.839649
G1 F2387.874
G1 X123.69 Y118.405 E.24532
G1 X123.696 Y118.402 F30000
; LINE_WIDTH: 0.666699
G1 F3000
G1 X124.717 Y120.118 E.18904
G1 X128.098 Y119.264 F30000
; LINE_WIDTH: 0.666688
G1 F3000
G1 X128.072 Y117.268 E.18901
G1 X128.065 Y117.268 F30000
; LINE_WIDTH: 0.839662
G1 F2387.834
G1 X128.09 Y119.264 E.24528
G1 X128.064 Y119.264 F30000
; LINE_WIDTH: 1.04714
G1 F1872.47
G1 X128.069 Y118.875 E.06088
; LINE_WIDTH: 0.998362
G1 F1972.556
G1 X128.073 Y118.487 E.05779
; LINE_WIDTH: 0.973974
G1 F2026.722
G1 X128.058 Y117.268 E.17647
; WIPE_START
G1 F24000
G1 X128.073 Y118.487 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X132.416 Y118.467 Z8 F30000
G1 Z7.6
G1 E3 F1800
; LINE_WIDTH: 0.968722
G1 F2038.778
G1 X131.82 Y119.53 E.17542
; LINE_WIDTH: 0.998391
G1 F1972.495
M73 P87 R1
G1 X131.748 Y119.653 E.02116
; LINE_WIDTH: 1.06346
G1 F1841.214
G1 X131.675 Y119.775 E.02267
G1 X130.975 Y119.892 E.11301
G1 X131.446 Y120.212 F30000
; LINE_WIDTH: 0.821343
G1 F2447.309
G1 X132.422 Y118.47 E.23935
G1 X132.428 Y118.474 F30000
; LINE_WIDTH: 0.650193
G1 F3000
G1 X131.452 Y120.216 E.18366
; WIPE_START
G1 F24000
G1 X132.428 Y118.474 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X135.591 Y121.684 Z8 F30000
G1 Z7.6
G1 E3 F1800
; LINE_WIDTH: 0.968716
G1 F2038.792
G1 X134.543 Y122.307 E.17541
; LINE_WIDTH: 0.998372
G1 F1972.536
G1 X134.419 Y122.377 E.02115
; LINE_WIDTH: 1.06341
G1 F1841.295
G1 X134.295 Y122.446 E.02266
G1 X133.633 Y122.197 E.11282
G1 X133.878 Y122.71 F30000
; LINE_WIDTH: 0.821354
G1 F2447.27
G1 X135.595 Y121.69 E.23934
G1 X135.598 Y121.696 F30000
; LINE_WIDTH: 0.650167
G1 F3000
G1 X133.882 Y122.717 E.18364
G1 X132.465 Y123.666 F30000
; LINE_WIDTH: 0.680767
G1 F3000
G1 X132.23 Y123.292 E.04282
; LINE_WIDTH: 0.643249
G2 X131.692 Y122.61 I-1.849 J.904 E.07951
; LINE_WIDTH: 0.676932
G2 X131.193 Y122.138 I-16.447 J16.881 E.06613
; LINE_WIDTH: 0.694933
G1 F2955.215
G1 X130.998 Y121.976 E.02526
; LINE_WIDTH: 0.724048
G1 F2820.399
G2 X130.774 Y121.791 I-3.524 J4.04 E.03014
; LINE_WIDTH: 0.75469
G1 F2691.189
G1 X130.674 Y121.717 E.01366
; LINE_WIDTH: 0.77193
G1 F2623.565
G2 X130.336 Y121.534 I-.589 J.687 E.04324
; LINE_WIDTH: 0.7369
G1 F2764.727
G1 X130.304 Y121.52 E.00374
; LINE_WIDTH: 0.720796
G1 F2834.846
G1 X130.067 Y121.428 E.02633
; LINE_WIDTH: 0.682242
G1 F3000
G2 X128.757 Y121.044 I-2.368 J5.653 E.13288
; LINE_WIDTH: 0.701952
G1 F2921.548
G1 X128.506 Y121.003 E.02556
; LINE_WIDTH: 0.735388
G1 F2771.162
G2 X128.219 Y120.957 I-.993 J5.283 E.03076
; LINE_WIDTH: 0.765442
G1 F2648.612
G1 X128.049 Y120.939 E.01894
G1 X127.711 Y120.974 E.03765
; LINE_WIDTH: 0.72496
G1 F2816.376
G1 X127.677 Y120.979 E.0036
; LINE_WIDTH: 0.686406
G1 F2997.176
G2 X126.104 Y121.356 I.791 J6.776 E.15872
; LINE_WIDTH: 0.710226
G1 F2882.835
G1 X125.866 Y121.448 E.02591
; LINE_WIDTH: 0.748007
G1 F2718.351
G2 X125.595 Y121.554 I1.827 J5.073 E.03146
; LINE_WIDTH: 0.781139
G1 F2588.817
G1 X125.512 Y121.591 E.01033
; LINE_WIDTH: 0.773343
G1 F2618.172
G1 X125.343 Y121.716 E.0235
; LINE_WIDTH: 0.732455
G1 F2783.73
G2 X125.148 Y121.862 I2.606 J3.7 E.02568
; LINE_WIDTH: 0.685389
G1 F3000
G2 X123.985 Y122.987 I4.228 J5.534 E.15845
; LINE_WIDTH: 0.719738
G1 F2839.577
G1 X123.827 Y123.186 E.02633
; LINE_WIDTH: 0.762841
G1 F2658.789
G2 X123.639 Y123.425 I3.3 J2.779 E.03353
; LINE_WIDTH: 0.768563
G1 F2636.505
G1 X123.542 Y123.655 E.02774
; LINE_WIDTH: 0.724678
G1 F2817.619
G2 X123.432 Y123.915 I4.779 J2.171 E.02944
; LINE_WIDTH: 0.685254
G1 F3000
G2 X123.003 Y125.476 I6.595 J2.651 E.15844
; LINE_WIDTH: 0.729223
G1 F2797.715
G1 X122.97 Y125.713 E.02514
; LINE_WIDTH: 0.772443
G1 F2621.605
G2 X122.943 Y126.019 I.669 J.213 E.03457
; LINE_WIDTH: 0.755471
G1 F2688.049
G1 X122.975 Y126.271 E.0278
; LINE_WIDTH: 0.71496
G1 F2861.141
G2 X123.013 Y126.556 I5.315 J-.56 E.0295
; LINE_WIDTH: 0.685988
G1 F2999.265
G2 X123.438 Y128.119 I7.092 J-1.091 E.15869
; LINE_WIDTH: 0.73746
G1 F2762.348
G1 X123.515 Y128.303 E.02124
; LINE_WIDTH: 0.774825
G1 F2612.54
G2 X123.676 Y128.609 I.928 J-.295 E.03896
; LINE_WIDTH: 0.742251
G1 F2742.188
G1 X123.832 Y128.81 E.02724
; LINE_WIDTH: 0.691406
G1 F2972.43
G2 X124.312 Y129.386 I5.839 J-4.378 E.07402
; LINE_WIDTH: 0.677764
G1 F3000
G1 X124.364 Y129.443 E.00744
G2 X124.755 Y129.816 I15.724 J-16.058 E.05209
; LINE_WIDTH: 0.701579
G1 F2923.321
G1 X125.144 Y130.144 E.05104
; LINE_WIDTH: 0.727726
G1 F2804.241
G1 X125.171 Y130.165 E.00363
; LINE_WIDTH: 0.746333
G1 F2725.24
G1 X125.299 Y130.262 E.01726
; LINE_WIDTH: 0.773009
G1 F2619.447
G2 X125.632 Y130.452 I.836 J-1.076 E.04317
; LINE_WIDTH: 0.730301
G1 F2793.037
G1 X125.869 Y130.547 E.02673
; LINE_WIDTH: 0.683296
G1 F3000
G2 X127.175 Y130.943 I2.421 J-5.631 E.13313
; LINE_WIDTH: 0.695704
G1 F2951.483
G1 X127.425 Y130.985 E.02529
; LINE_WIDTH: 0.72533
G1 F2814.745
G2 X127.711 Y131.033 I1.027 J-5.265 E.03021
; LINE_WIDTH: 0.755856
G1 F2686.507
G1 X127.831 Y131.047 E.01317
; LINE_WIDTH: 0.771281
G1 F2626.051
G2 X128.219 Y131.034 I.165 J-.902 E.04374
; LINE_WIDTH: 0.735408
G1 F2771.076
G1 X128.254 Y131.03 E.00372
; LINE_WIDTH: 0.719581
G1 F2840.282
G1 X128.506 Y130.991 E.02627
; LINE_WIDTH: 0.682146
G1 F3000
G2 X129.831 Y130.667 I-.788 J-6.097 E.13286
; LINE_WIDTH: 0.702872
G1 F2917.193
G1 X130.069 Y130.577 E.0256
; LINE_WIDTH: 0.736825
G1 F2765.044
G2 X130.34 Y130.473 I-1.788 J-5.075 E.03084
; LINE_WIDTH: 0.764908
G1 F2650.693
G1 X130.488 Y130.408 E.01787
G1 X130.77 Y130.202 E.03866
; LINE_WIDTH: 0.700592
G1 F2928.011
G2 X131.192 Y129.86 I-6.122 J-7.969 E.05441
; LINE_WIDTH: 0.665165
G1 F3000
G2 X131.997 Y129.084 I-9.255 J-10.408 E.10557
; LINE_WIDTH: 0.651976
G1 X132.242 Y128.702 E.0419
; LINE_WIDTH: 0.672683
G1 X132.488 Y128.32 E.04343
G1 X132.21 Y127.318 F30000
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.8828
G1 F2258.585
G1 X132.338 Y127.313 E.01671
G1 X132.656 Y127.518 E.04912
G2 X133.016 Y126.049 I-15.323 J-4.533 E.19658
G1 X132.75 Y124.789 E.1673
G1 X132.649 Y124.455 E.04523
G1 X132.275 Y124.691 E.05746
G1 X132.21 Y124.676 E.00868
G1 X132.21 Y127.198 E.32751
G1 X134.694 Y126.07 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 1.0703
G1 F1828.417
G1 X135.228 Y126.069 E.08575
; LINE_WIDTH: 1.04909
G1 F1868.684
G1 X135.361 Y126.073 E.02088
; LINE_WIDTH: 1.01146
G1 F1944.646
G1 X136.047 Y126.072 E.10339
; LINE_WIDTH: 0.978637
G1 F2016.137
G1 X136.732 Y126.072 E.09972
; WIPE_START
G1 F24000
G1 X136.047 Y126.072 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X135.533 Y130.416 Z8 F30000
G1 Z7.6
G1 E3 F1800
; LINE_WIDTH: 0.968718
G1 F2038.789
G1 X134.47 Y129.82 E.17541
; LINE_WIDTH: 0.998389
G1 F1972.498
G1 X134.347 Y129.748 E.02116
; LINE_WIDTH: 1.06346
G1 F1841.215
G1 X134.225 Y129.675 E.02267
G1 X134.108 Y128.975 E.11305
G1 X133.788 Y129.446 F30000
; LINE_WIDTH: 0.821342
G1 F2447.309
G1 X135.53 Y130.422 E.23935
G1 X135.526 Y130.428 F30000
; LINE_WIDTH: 0.650192
G1 F3000
G1 X133.784 Y129.452 E.18366
; WIPE_START
G1 F24000
G1 X135.526 Y130.428 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X132.316 Y133.591 Z8 F30000
G1 Z7.6
G1 E3 F1800
; LINE_WIDTH: 0.968715
G1 F2038.795
G1 X131.693 Y132.543 E.17541
; LINE_WIDTH: 0.998384
G1 F1972.509
G1 X131.623 Y132.419 E.02117
; LINE_WIDTH: 1.06347
G1 F1841.198
G1 X131.554 Y132.295 E.02268
G1 X131.803 Y131.632 E.11289
G1 X131.29 Y131.878 F30000
; LINE_WIDTH: 0.821346
G1 F2447.298
G1 X132.31 Y133.595 E.23936
G1 X132.304 Y133.598 F30000
; LINE_WIDTH: 0.650178
G1 F3000
G1 X131.283 Y131.882 E.18366
G1 X127.93 Y132.694 F30000
; LINE_WIDTH: 1.07529
G1 F1819.191
G1 X127.931 Y133.228 E.08619
; LINE_WIDTH: 1.04908
G1 F1868.693
G1 X127.927 Y133.361 E.02087
; LINE_WIDTH: 1.01146
G1 F1944.638
G1 X127.928 Y134.047 E.10339
; LINE_WIDTH: 0.995054
G1 F1979.734
G1 X127.928 Y134.732 E.10156
; WIPE_START
G1 F24000
G1 X127.928 Y134.047 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X124.548 Y131.784 Z8 F30000
G1 Z7.6
G1 E3 F1800
; LINE_WIDTH: 0.666708
G1 F3000
G1 X123.572 Y133.526 E.18905
G1 X123.578 Y133.53 F30000
; LINE_WIDTH: 0.83964
G1 F2387.904
G1 X124.554 Y131.788 E.24532
G1 X124.576 Y131.801 F30000
; LINE_WIDTH: 1.04724
G1 F1872.27
G1 X124.378 Y132.135 E.06092
; LINE_WIDTH: 0.998403
G1 F1972.469
G1 X124.18 Y132.47 E.05782
; LINE_WIDTH: 0.973982
G1 F2026.703
G1 X123.584 Y133.533 E.17646
; CHANGE_LAYER
; Z_HEIGHT: 8
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X124.18 Y132.47 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 20/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L20
M991 S0 P19 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z8 I.964 J.743 P1  F30000
G1 X131.344 Y123.183 Z8
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2412
G1 X131.444 Y123.276 E.01641
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X127.949 Y121.661 I-2.779 J-3.337 E1.98696
G3 X130.78 Y122.66 I.043 J4.388 E.36658
G1 X131.256 Y123.101 E.07761
G1 X130.71 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2412
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X127.954 Y122.395 I-2.309 J-2.773 E1.65039
G1 X128.17 Y122.393 E.02576
G3 X130.627 Y123.509 I-.217 J3.743 E.33037
M204 S10000
; WIPE_START
G1 F24000
G1 X130.661 Y125.509 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.806 Y128.866 Z8.4 F30000
G1 X122.949 Y129.285 Z8.4
G1 Z8
G1 E3 F1800
; FEATURE: Inner wall
G1 F2412
G1 X122.731 Y128.923 E.05056
G1 X122.974 Y128.763 E.03484
G3 X122.272 Y126.327 I10.919 J-4.464 E.30396
G1 X121.983 Y126.32 E.03466
G1 X121.975 Y125.897 E.05056
G1 X122.266 Y125.88 E.03487
G3 X122.877 Y123.419 I11.687 J1.594 E.30396
G1 X122.629 Y123.268 E.03465
G1 X122.834 Y122.899 E.05056
G1 X123.094 Y123.029 E.03486
G3 X124.853 Y121.203 I9.325 J7.224 E.30396
G1 X124.715 Y120.949 E.03463
G1 X125.077 Y120.731 E.05056
G1 X125.237 Y120.974 E.03484
G3 X127.673 Y120.272 I4.464 J10.919 E.30396
G1 X127.683 Y119.848 E.05074
G1 X128.102 Y119.837 E.05014
G1 X128.135 Y120.269 E.05176
G3 X130.581 Y120.877 I-1.594 J11.637 E.30211
G1 X130.732 Y120.629 E.03466
G1 X131.101 Y120.834 E.05056
G1 X130.971 Y121.094 E.03487
G3 X132.797 Y122.853 I-7.225 J9.326 E.30396
G1 X133.051 Y122.715 E.03464
G1 X133.269 Y123.077 E.05056
G1 X133.026 Y123.237 E.03485
G3 X133.728 Y125.673 I-10.919 J4.464 E.30396
G1 X134.017 Y125.68 E.03466
G1 X134.025 Y126.103 E.05056
G1 X133.734 Y126.12 E.03487
G3 X133.123 Y128.581 I-11.689 J-1.594 E.30396
G1 X133.371 Y128.731 E.03461
G1 X133.166 Y129.101 E.05056
G1 X132.906 Y128.971 E.03482
G3 X131.147 Y130.797 I-9.325 J-7.224 E.30396
G1 X131.285 Y131.051 E.03464
G1 X130.924 Y131.269 E.05056
G1 X130.763 Y131.026 E.03485
G3 X128.327 Y131.728 I-4.464 J-10.919 E.30396
G1 X128.32 Y132.017 E.03466
G1 X127.897 Y132.025 E.05056
G1 X127.88 Y131.734 E.03487
G3 X125.419 Y131.123 I1.594 J-11.688 E.30396
G1 X125.269 Y131.371 E.0346
G1 X124.899 Y131.166 E.05056
G1 X125.029 Y130.906 E.03481
G3 X123.203 Y129.147 I7.223 J-9.324 E.30396
G1 X123.054 Y129.228 E.02027
G1 X122.977 Y130.107 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2412
G3 X120.389 Y130.989 I-3.541 J-6.152 E.32914
G1 X120.302 Y130.852 E.01946
G3 X120.027 Y130.388 I5.179 J-3.385 E.0646
G3 X122.086 Y128.47 I5.799 J4.162 E.33891
G3 X121.677 Y127.047 I8.617 J-3.25 E.17731
G1 X121.596 Y127.045 E.00963
G3 X118.914 Y126.515 I.009 J-7.099 E.32914
G1 X118.908 Y126.353 E.01946
G3 X118.901 Y125.813 I6.177 J-.342 E.0646
G3 X121.643 Y125.182 I2.941 J6.504 E.33891
G3 X122 Y123.745 I9.087 J1.494 E.17731
G1 X121.931 Y123.703 E.00964
G3 X119.874 Y121.903 I3.557 J-6.143 E.32914
G1 X119.949 Y121.759 E.01946
G3 X120.214 Y121.289 I5.52 J2.792 E.0646
G3 X122.904 Y122.113 I-.705 J7.103 E.33891
G3 X123.931 Y121.047 I7.123 J5.837 E.17731
G1 X123.893 Y120.977 E.00963
G3 X123.011 Y118.389 I6.152 J-3.541 E.32914
G1 X123.148 Y118.302 E.01946
G3 X123.612 Y118.027 I3.385 J5.179 E.0646
G3 X125.53 Y120.086 I-4.162 J5.799 E.33891
G3 X126.953 Y119.677 I3.25 J8.617 E.17731
G1 X126.955 Y119.596 E.00964
G3 X127.485 Y116.914 I7.099 J.009 E.32914
G1 X127.647 Y116.908 E.01942
G3 X128.187 Y116.901 I.372 J8.645 E.06463
G3 X128.824 Y119.644 I-6.607 J2.979 E.3391
G3 X130.255 Y120 I-1.497 J9.078 E.17665
M73 P88 R1
G1 X130.297 Y119.931 E.00963
G3 X132.097 Y117.874 I6.143 J3.557 E.32914
G1 X132.241 Y117.949 E.01946
G3 X132.711 Y118.214 I-2.792 J5.52 E.0646
G3 X131.887 Y120.904 I-7.103 J-.705 E.33891
G3 X132.953 Y121.931 I-5.838 J7.123 E.17731
G1 X133.023 Y121.893 E.00963
G3 X135.611 Y121.011 I3.541 J6.152 E.32914
G1 X135.698 Y121.148 E.01946
G3 X135.973 Y121.612 I-5.178 J3.385 E.0646
G3 X133.914 Y123.53 I-5.799 J-4.162 E.33891
G3 X134.323 Y124.953 I-8.617 J3.25 E.17731
G1 X134.404 Y124.955 E.00963
G3 X137.086 Y125.485 I-.009 J7.099 E.32914
G1 X137.092 Y125.647 E.01946
G3 X137.099 Y126.187 I-6.177 J.342 E.0646
G3 X134.357 Y126.818 I-2.941 J-6.504 E.33891
G3 X134 Y128.255 I-9.088 J-1.494 E.17731
G1 X134.069 Y128.297 E.00963
G3 X136.126 Y130.097 I-3.557 J6.143 E.32914
G1 X136.051 Y130.241 E.01946
G3 X135.786 Y130.711 I-5.521 J-2.792 E.0646
G3 X133.096 Y129.887 I.705 J-7.103 E.33891
G3 X132.069 Y130.953 I-7.123 J-5.838 E.17731
G1 X132.107 Y131.023 E.00963
G3 X132.989 Y133.611 I-6.152 J3.541 E.32914
G1 X132.852 Y133.698 E.01946
G3 X132.388 Y133.973 I-3.385 J-5.178 E.0646
G3 X130.47 Y131.914 I4.162 J-5.799 E.33891
G3 X129.047 Y132.323 I-3.25 J-8.617 E.17731
G1 X129.045 Y132.404 E.00963
G3 X128.515 Y135.086 I-7.099 J-.009 E.32914
G1 X128.353 Y135.092 E.01946
G3 X127.813 Y135.099 I-.342 J-6.178 E.0646
G3 X127.182 Y132.357 I6.504 J-2.941 E.33891
G3 X125.745 Y132 I1.494 J-9.088 E.17731
G1 X125.703 Y132.069 E.00964
G3 X123.903 Y134.126 I-6.143 J-3.557 E.32914
G1 X123.759 Y134.051 E.01946
G3 X123.289 Y133.786 I2.792 J-5.52 E.0646
G3 X124.113 Y131.096 I7.103 J.705 E.33891
G3 X123.073 Y130.098 I5.837 J-7.122 E.17259
M204 S10000
G1 X122.526 Y129.294 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 1.13014
G1 F1723.637
G1 X122.174 Y129.506 E.06994
; LINE_WIDTH: 1.09372
G1 F1785.926
G2 X121.806 Y129.727 I4.32 J7.597 E.0704
; LINE_WIDTH: 1.04716
G1 F1872.418
G1 X121.684 Y129.8 E.02231
; LINE_WIDTH: 0.998295
G1 F1972.701
G1 X121.562 Y129.873 E.02118
; LINE_WIDTH: 0.97386
G1 F2026.982
G1 X120.532 Y130.525 E.17645
G1 X120.528 Y130.519 F30000
; LINE_WIDTH: 0.839554
G1 F2388.177
G1 X122.509 Y129.266 E.2879
G1 X121.612 Y126.116 F30000
; LINE_WIDTH: 1.1301
G1 F1723.702
G1 X121.201 Y126.123 E.06992
; LINE_WIDTH: 1.09371
G1 F1785.954
G2 X120.773 Y126.131 I-.057 J8.738 E.07037
; LINE_WIDTH: 1.04717
G1 F1872.401
G1 X120.63 Y126.133 E.02231
; LINE_WIDTH: 0.998306
G1 F1972.677
G1 X120.488 Y126.135 E.02118
; LINE_WIDTH: 0.973872
G1 F2026.956
G1 X119.27 Y126.185 E.17646
G1 X119.27 Y126.177 F30000
; LINE_WIDTH: 0.839555
G1 F2388.172
G1 X121.611 Y126.083 E.28787
G1 X122.41 Y122.906 F30000
; LINE_WIDTH: 1.13012
G1 F1723.682
G1 X122.051 Y122.707 E.06992
; LINE_WIDTH: 1.09371
G1 F1785.948
G2 X121.676 Y122.5 I-4.426 J7.551 E.07038
; LINE_WIDTH: 1.04717
G1 F1872.413
G1 X121.551 Y122.43 E.02231
; LINE_WIDTH: 0.998303
G1 F1972.684
G1 X121.427 Y122.361 E.02118
; LINE_WIDTH: 0.973869
G1 F2026.962
G1 X120.347 Y121.795 E.17646
G1 X120.351 Y121.788 F30000
; LINE_WIDTH: 0.839556
G1 F2388.168
G1 X122.426 Y122.878 E.28788
G1 X124.706 Y120.526 F30000
; LINE_WIDTH: 1.13015
G1 F1723.635
G1 X124.494 Y120.174 E.06994
; LINE_WIDTH: 1.09372
G1 F1785.931
G2 X124.273 Y119.806 I-7.6 J4.322 E.0704
; LINE_WIDTH: 1.04717
G1 F1872.413
G1 X124.2 Y119.684 E.02231
; LINE_WIDTH: 0.998302
G1 F1972.687
G1 X124.127 Y119.562 E.02118
; LINE_WIDTH: 0.973869
G1 F2026.961
G1 X123.475 Y118.532 E.17646
G1 X123.481 Y118.528 F30000
; LINE_WIDTH: 0.839551
G1 F2388.184
G1 X124.734 Y120.509 E.2879
G1 X127.876 Y119.476 F30000
; LINE_WIDTH: 1.11142
G1 F1755.105
G2 X127.869 Y118.773 I-14.309 J-.202 E.11757
; LINE_WIDTH: 1.04898
G1 F1868.893
G1 X127.868 Y118.64 E.02087
; LINE_WIDTH: 1.01136
G1 F1944.858
G1 X127.849 Y117.955 E.10338
; LINE_WIDTH: 0.994946
G1 F1979.968
G1 X127.829 Y117.27 E.10155
; WIPE_START
G1 F24000
G1 X127.849 Y117.955 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X131.122 Y120.426 Z8.4 F30000
G1 Z8
G1 E3 F1800
; LINE_WIDTH: 0.821248
G1 F2412
G1 X132.212 Y118.349 E.28111
G1 X132.206 Y118.345 F30000
; LINE_WIDTH: 0.968615
G1 F2039.027
G1 X131.639 Y119.427 E.17567
; LINE_WIDTH: 0.998303
G1 F1972.684
G1 X131.57 Y119.551 E.02118
; LINE_WIDTH: 1.04717
G1 F1872.404
G1 X131.5 Y119.676 E.02231
; LINE_WIDTH: 1.07418
G1 F1821.23
G1 X131.492 Y119.691 E.00283
; LINE_WIDTH: 1.09454
G1 F1784.474
G1 X131.422 Y119.818 E.02389
; LINE_WIDTH: 1.14212
G1 F1704.1
G1 X131.351 Y119.945 E.02501
G1 X131.602 Y120.653 E.12919
G1 X133.214 Y122.207 F30000
; LINE_WIDTH: 1.14214
G1 F1704.058
G1 X133.929 Y122.432 E.1291
G1 X134.054 Y122.358 E.02503
; LINE_WIDTH: 1.09455
G1 F1784.459
G1 X134.179 Y122.283 E.0239
; LINE_WIDTH: 1.07418
G1 F1821.231
G1 X134.194 Y122.273 E.00283
; LINE_WIDTH: 1.04717
G1 F1872.404
G1 X134.316 Y122.2 E.02231
; LINE_WIDTH: 0.998302
G1 F1972.688
G1 X134.438 Y122.127 E.02118
; LINE_WIDTH: 0.96862
G1 F2039.014
G1 X135.47 Y121.474 E.17567
G1 X135.474 Y121.48 F30000
; LINE_WIDTH: 0.821226
G1 F2412
G1 X133.491 Y122.734 E.28112
G1 X134.389 Y125.917 F30000
; LINE_WIDTH: 0.821252
G1 F2412
G1 X136.73 Y125.823 E.28088
G1 X136.73 Y125.815 F30000
; LINE_WIDTH: 0.968619
G1 F2039.018
G1 X135.512 Y125.865 E.17542
; LINE_WIDTH: 0.998305
G1 F1972.679
G1 X135.37 Y125.867 E.02118
; LINE_WIDTH: 1.04717
G1 F1872.407
G1 X135.227 Y125.869 E.02231
; LINE_WIDTH: 1.07418
G1 F1821.235
G1 X135.21 Y125.87 E.00283
; LINE_WIDTH: 1.09454
G1 F1784.477
G1 X135.064 Y125.873 E.02389
; LINE_WIDTH: 1.14211
G1 F1704.103
G1 X134.919 Y125.875 E.02501
G1 X134.412 Y125.322 E.1291
G1 X132.205 Y124.699 F30000
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.873029
G1 F2286.62
G1 X132.205 Y127.334 E.33809
G1 X132.27 Y127.318 E.00859
G1 X132.648 Y127.549 E.0568
G1 X132.764 Y127.17 E.05088
G1 X133 Y125.906 E.16496
G1 X132.716 Y124.647 E.16562
G1 X132.658 Y124.484 E.02217
G1 X132.317 Y124.701 E.05186
G1 X132.487 Y123.691 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 0.686082
G1 F2412
G1 X132.241 Y123.304 E.04484
; LINE_WIDTH: 0.64748
G1 X131.995 Y122.918 E.04196
G1 X131.646 Y122.564 E.04547
; LINE_WIDTH: 0.682632
G2 X130.765 Y121.806 I-5.196 J5.147 E.11314
; LINE_WIDTH: 0.72324
G1 X130.604 Y121.692 E.02052
; LINE_WIDTH: 0.755869
G2 X130.305 Y121.517 I-.691 J.84 E.038
; LINE_WIDTH: 0.726556
G1 X130.068 Y121.426 E.02657
; LINE_WIDTH: 0.685741
G2 X128.219 Y120.976 I-2.384 J5.779 E.18668
; LINE_WIDTH: 0.730914
G1 X128.062 Y120.963 E.0166
; LINE_WIDTH: 0.754109
G2 X127.677 Y120.976 I-.142 J1.52 E.04211
; LINE_WIDTH: 0.703924
G1 X127.175 Y121.059 E.05124
; LINE_WIDTH: 0.684995
G2 X125.637 Y121.558 I1.087 J5.965 E.15831
; LINE_WIDTH: 0.725149
G1 X125.606 Y121.572 E.0036
; LINE_WIDTH: 0.749419
G2 X125.173 Y121.838 I.464 J1.24 E.0553
; LINE_WIDTH: 0.684823
G2 X123.993 Y122.992 I3.98 J5.251 E.16153
; LINE_WIDTH: 0.694359
G1 X123.84 Y123.195 E.02523
; LINE_WIDTH: 0.722933
G2 X123.666 Y123.427 I4.206 J3.327 E.03007
; LINE_WIDTH: 0.746832
G2 X123.442 Y123.883 I1.053 J.802 E.0551
; LINE_WIDTH: 0.683212
G2 X123.014 Y125.476 I6.144 J2.501 E.16103
; LINE_WIDTH: 0.701226
G1 X122.985 Y125.729 E.02553
; LINE_WIDTH: 0.734123
G2 X122.953 Y126.018 I5.326 J.738 E.03069
; LINE_WIDTH: 0.762229
G1 X122.949 Y126.095 E.00854
; LINE_WIDTH: 0.753978
G1 X122.977 Y126.31 E.02355
; LINE_WIDTH: 0.717332
G2 X123.011 Y126.557 I4.606 J-.507 E.02568
; LINE_WIDTH: 0.681953
G2 X123.45 Y128.112 I6.26 J-.927 E.15746
; LINE_WIDTH: 0.709336
G1 X123.554 Y128.345 E.02588
; LINE_WIDTH: 0.746561
G2 X123.673 Y128.611 I2.77 J-1.085 E.03138
; LINE_WIDTH: 0.749246
G1 X123.83 Y128.811 E.02754
; LINE_WIDTH: 0.710781
G2 X124.008 Y129.037 I4.28 J-3.19 E.02928
; LINE_WIDTH: 0.681952
G2 X125.179 Y130.152 I4.992 J-4.071 E.15748
; LINE_WIDTH: 0.716988
G1 X125.368 Y130.287 E.02391
; LINE_WIDTH: 0.754417
G2 X125.631 Y130.456 I.563 J-.59 E.03425
; LINE_WIDTH: 0.73663
G1 X125.868 Y130.549 E.027
; LINE_WIDTH: 0.685651
G2 X127.711 Y131.016 I2.461 J-5.845 E.18661
; LINE_WIDTH: 0.724115
G1 X127.903 Y131.033 E.02006
; LINE_WIDTH: 0.755818
G2 X128.254 Y131.033 I.176 J-1.118 E.0385
; LINE_WIDTH: 0.725263
G1 X128.506 Y130.994 E.02652
; LINE_WIDTH: 0.685801
G2 X130.33 Y130.456 I-.829 J-6.184 E.18671
; LINE_WIDTH: 0.731869
G1 X130.469 Y130.391 E.01613
; LINE_WIDTH: 0.753717
G2 X130.799 Y130.183 I-.676 J-1.442 E.04259
; LINE_WIDTH: 0.693738
G2 X131.432 Y129.642 I-4.914 J-6.382 E.08252
; LINE_WIDTH: 0.669646
G2 X131.782 Y129.298 I-8.325 J-8.825 E.04667
; LINE_WIDTH: 0.625003
G1 X131.991 Y129.078 E.0267
G1 X132.453 Y128.322 E.07788
G1 X133.574 Y129.122 F30000
; LINE_WIDTH: 0.821236
G1 F2412
G1 X135.649 Y130.212 E.28092
G1 X135.653 Y130.205 F30000
; LINE_WIDTH: 0.968611
G1 F2039.035
G1 X134.573 Y129.639 E.17541
; LINE_WIDTH: 0.998301
G1 F1972.689
G1 X134.449 Y129.57 E.02118
; LINE_WIDTH: 1.04716
G1 F1872.419
G1 X134.324 Y129.5 E.02231
; LINE_WIDTH: 1.07418
G1 F1821.241
G1 X134.309 Y129.492 E.00283
; LINE_WIDTH: 1.09456
G1 F1784.441
G1 X134.181 Y129.422 E.02391
; LINE_WIDTH: 1.14218
G1 F1703.997
G1 X134.054 Y129.351 E.02504
G1 X133.892 Y128.619 E.1291
G1 X131.793 Y131.214 F30000
; LINE_WIDTH: 1.14214
G1 F1704.061
G1 X131.568 Y131.929 E.1291
G1 X131.642 Y132.054 E.02502
; LINE_WIDTH: 1.09456
G1 F1784.449
G1 X131.717 Y132.179 E.02389
; LINE_WIDTH: 1.07419
G1 F1821.224
G1 X131.727 Y132.194 E.00283
; LINE_WIDTH: 1.04717
G1 F1872.404
G1 X131.8 Y132.316 E.02232
; LINE_WIDTH: 0.998298
G1 F1972.694
G1 X131.873 Y132.438 E.02118
; LINE_WIDTH: 0.968617
G1 F2039.022
G1 X132.525 Y133.468 E.17541
G1 X132.519 Y133.472 F30000
; LINE_WIDTH: 0.821225
G1 F2412
G1 X131.266 Y131.491 E.28089
G1 X128.116 Y132.388 F30000
; LINE_WIDTH: 1.1301
G1 F1723.702
G1 X128.123 Y132.799 E.06992
; LINE_WIDTH: 1.0937
G1 F1785.956
G2 X128.131 Y133.227 I8.755 J.057 E.07037
; LINE_WIDTH: 1.04717
G1 F1872.407
G1 X128.133 Y133.37 E.02231
; LINE_WIDTH: 0.998305
G1 F1972.679
G1 X128.135 Y133.512 E.02118
; LINE_WIDTH: 0.973873
G1 F2026.954
G1 X128.185 Y134.73 E.17646
G1 X128.177 Y134.73 F30000
; LINE_WIDTH: 0.839552
G1 F2388.183
G1 X128.083 Y132.389 E.28787
G1 X124.907 Y131.59 F30000
; LINE_WIDTH: 1.13018
G1 F1723.572
G1 X124.707 Y131.949 E.06996
; LINE_WIDTH: 1.09373
G1 F1785.911
G2 X124.5 Y132.324 I7.545 J4.422 E.07042
; LINE_WIDTH: 1.04716
G1 F1872.419
G1 X124.43 Y132.449 E.02231
; LINE_WIDTH: 0.998302
G1 F1972.687
G1 X124.361 Y132.573 E.02118
; LINE_WIDTH: 0.973871
G1 F2026.957
G1 X123.795 Y133.653 E.17646
G1 X123.788 Y133.649 F30000
; LINE_WIDTH: 0.839555
G1 F2388.174
G1 X124.878 Y131.574 E.28793
; CHANGE_LAYER
; Z_HEIGHT: 8.4
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X123.948 Y133.345 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 21/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L21
M991 S0 P20 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z8.4 I.984 J.716 P1  F30000
G1 X131.344 Y123.183 Z8.4
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2451.784
G1 X131.444 Y123.276 E.01643
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X127.922 Y121.661 I-2.777 J-3.338 E1.98278
G3 X130.78 Y122.66 I.07 J4.389 E.36989
G1 X131.256 Y123.101 E.0776
G1 X130.71 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X127.927 Y122.395 I-2.307 J-2.773 E1.64636
G1 X128.17 Y122.393 E.02906
G3 X130.627 Y123.509 I-.217 J3.743 E.33037
M204 S10000
; WIPE_START
G1 F24000
G1 X130.661 Y125.509 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X124.192 Y129.56 Z8.8 F30000
G1 X123.8 Y129.806 Z8.8
G1 Z8.4
G1 E3 F1800
; FEATURE: Inner wall
G1 F2451.784
G1 X123.304 Y129.309 E.08397
G1 X122.789 Y129.586 E.06994
G1 X122.57 Y129.236 E.04936
G1 X123.028 Y128.906 E.06757
G3 X122.278 Y126.518 I14.377 J-5.829 E.29986
G1 X121.694 Y126.5 E.06993
G1 X121.68 Y126.087 E.04936
G1 X122.241 Y126.031 E.06757
G3 X122.786 Y123.587 I15.365 J2.14 E.29987
G1 X122.289 Y123.28 E.06994
G1 X122.483 Y122.916 E.04936
G1 X122.997 Y123.148 E.06757
G3 X124.691 Y121.304 I12.235 J9.535 E.29986
G1 X124.414 Y120.789 E.06995
G1 X124.764 Y120.57 E.04936
G1 X125.094 Y121.028 E.06758
G3 X127.482 Y120.278 I5.829 J14.377 E.29986
G1 X127.5 Y119.694 E.06994
G1 X127.913 Y119.679 E.04936
G1 X127.969 Y120.241 E.06757
G3 X130.413 Y120.786 I-2.14 J15.365 E.29986
G1 X130.72 Y120.289 E.06994
G1 X131.084 Y120.483 E.04936
G1 X130.852 Y120.997 E.06757
G3 X132.696 Y122.691 I-9.535 J12.235 E.29986
G1 X133.211 Y122.414 E.06994
G1 X133.43 Y122.764 E.04936
G1 X132.972 Y123.094 E.06758
M73 P89 R1
G3 X133.722 Y125.482 I-14.377 J5.829 E.29987
G1 X134.306 Y125.5 E.06994
G1 X134.321 Y125.913 E.04936
G1 X133.759 Y125.969 E.06757
G3 X133.214 Y128.413 I-15.365 J-2.14 E.29986
G1 X133.711 Y128.72 E.06994
G1 X133.517 Y129.084 E.04936
G1 X133.003 Y128.852 E.06757
G3 X131.309 Y130.696 I-12.235 J-9.535 E.29987
G1 X131.586 Y131.211 E.06994
G1 X131.236 Y131.43 E.04936
G1 X130.906 Y130.972 E.06757
G3 X128.518 Y131.722 I-5.829 J-14.377 E.29987
G1 X128.5 Y132.306 E.06993
G1 X128.087 Y132.32 E.04936
G1 X128.031 Y131.759 E.06757
G3 X125.587 Y131.214 I2.14 J-15.365 E.29987
G1 X125.28 Y131.711 E.06994
G1 X124.916 Y131.517 E.04936
G1 X125.148 Y131.003 E.06757
G3 X124.18 Y130.183 I9.535 J-12.235 E.15178
G1 X123.885 Y129.89 E.04972
G1 X123.103 Y130.251 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G3 X120.532 Y131.197 I-3.893 J-6.605 E.32952
G1 X120.439 Y131.064 E.01946
G3 X120.153 Y130.607 I9.821 J-6.465 E.0645
G3 X122.148 Y128.635 I5.944 J4.017 E.3378
G3 X121.706 Y127.235 I10.297 J-4.02 E.17588
G1 X121.634 Y127.232 E.00862
G3 X118.934 Y126.767 I-.069 J-7.667 E.32952
G1 X118.92 Y126.605 E.01946
G3 X118.9 Y126.066 I11.723 J-.687 E.06457
G3 X121.614 Y125.356 I3.136 J6.448 E.33778
G3 X121.932 Y123.922 I10.927 J1.667 E.17588
G1 X121.87 Y123.884 E.00862
G3 X119.765 Y122.131 I3.774 J-6.674 E.32952
G1 X119.834 Y121.984 E.01946
G3 X120.086 Y121.508 I10.511 J5.274 E.0645
G3 X122.791 Y122.249 I-.507 J7.156 E.3378
G3 X123.784 Y121.166 I8.629 J6.907 E.17588
G1 X123.749 Y121.103 E.00862
G3 X122.803 Y118.532 I6.605 J-3.893 E.32952
G1 X122.936 Y118.439 E.01946
G3 X123.393 Y118.153 I6.467 J9.825 E.0645
G3 X125.365 Y120.148 I-4.017 J5.944 E.3378
G3 X126.765 Y119.706 I4.02 J10.297 E.17588
G1 X126.768 Y119.634 E.00862
G3 X127.233 Y116.934 I7.667 J-.069 E.32952
G1 X127.395 Y116.92 E.01946
G3 X127.933 Y116.9 I1.161 J24.939 E.06449
G3 X128.644 Y119.614 I-6.573 J3.171 E.33773
G3 X130.078 Y119.932 I-1.667 J10.927 E.17588
G1 X130.116 Y119.87 E.00862
G3 X131.869 Y117.765 I6.674 J3.774 E.32952
G1 X132.016 Y117.834 E.01946
G3 X132.492 Y118.086 I-5.274 J10.512 E.0645
G3 X131.751 Y120.791 I-7.156 J-.507 E.3378
G3 X132.834 Y121.784 I-6.907 J8.629 E.17588
G1 X132.897 Y121.749 E.00862
G3 X135.468 Y120.803 I3.893 J6.605 E.32952
G1 X135.561 Y120.936 E.01946
G3 X135.847 Y121.393 I-9.822 J6.465 E.0645
G3 X133.852 Y123.365 I-5.944 J-4.017 E.3378
G3 X134.294 Y124.765 I-10.297 J4.02 E.17588
G1 X134.366 Y124.768 E.00862
G3 X137.066 Y125.233 I.069 J7.667 E.32952
G1 X137.08 Y125.395 E.01946
G3 X137.1 Y125.934 I-11.723 J.687 E.06457
G3 X134.386 Y126.644 I-3.136 J-6.448 E.33778
G3 X134.068 Y128.078 I-10.927 J-1.667 E.17588
G1 X134.13 Y128.116 E.00862
G3 X136.235 Y129.869 I-3.774 J6.674 E.32952
G1 X136.166 Y130.016 E.01946
G3 X135.914 Y130.492 I-10.51 J-5.274 E.0645
G3 X133.209 Y129.751 I.507 J-7.156 E.3378
G3 X132.216 Y130.834 I-8.629 J-6.907 E.17588
G1 X132.251 Y130.897 E.00862
G3 X133.197 Y133.468 I-6.605 J3.893 E.32952
G1 X133.064 Y133.561 E.01946
G3 X132.607 Y133.847 I-6.465 J-9.822 E.0645
G3 X130.635 Y131.852 I4.017 J-5.944 E.3378
G3 X129.235 Y132.294 I-4.02 J-10.297 E.17588
G1 X129.232 Y132.366 E.00862
G3 X128.767 Y135.066 I-7.667 J.069 E.32952
G1 X128.605 Y135.08 E.01946
G3 X128.066 Y135.1 I-.687 J-11.721 E.06457
G3 X127.356 Y132.386 I6.448 J-3.136 E.33778
G3 X125.922 Y132.068 I1.667 J-10.927 E.17588
G1 X125.884 Y132.13 E.00862
G3 X124.131 Y134.235 I-6.674 J-3.774 E.32952
G1 X123.984 Y134.166 E.01946
G3 X123.508 Y133.914 I5.273 J-10.508 E.0645
G3 X124.249 Y131.209 I7.156 J.507 E.3378
G3 X123.199 Y130.251 I6.907 J-8.629 E.17015
M204 S10000
; WIPE_START
G1 F24000
G1 X122.579 Y130.532 E-.97114
G1 X121.941 Y130.817 E-.99493
G1 X121.352 Y131.012 E-.88394
; WIPE_END
G1 E-.15 F1800
G1 X122.368 Y129.606 Z8.8 F30000
G1 Z8.4
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 1.07973
G1 F1811.059
G2 X121.912 Y129.897 I5.721 J9.446 E.08769
; LINE_WIDTH: 1.04726
G1 F1872.238
G1 X121.792 Y129.974 E.02231
; LINE_WIDTH: 0.998393
G1 F1972.491
G1 X121.672 Y130.05 E.02118
; LINE_WIDTH: 0.97396
G1 F2026.755
G1 X120.66 Y130.731 E.1765
G1 X122.354 Y129.584 F30000
; LINE_WIDTH: 0.839629
G1 F2387.937
G1 X120.656 Y130.725 E.25134
G1 X120.652 Y130.719 F30000
; LINE_WIDTH: 0.666671
G1 F3000
G1 X122.35 Y129.577 E.19368
G1 X121.32 Y126.301 F30000
; LINE_WIDTH: 1.07611
G1 F1817.695
G1 X120.779 Y126.332 E.0874
; LINE_WIDTH: 1.04907
G1 F1868.722
G1 X120.646 Y126.336 E.02087
; LINE_WIDTH: 1.01145
G1 F1944.663
G1 X119.962 Y126.375 E.1034
; LINE_WIDTH: 0.995039
G1 F1979.767
G1 X119.277 Y126.413 E.10157
G1 X119.277 Y126.413 F30000
; LINE_WIDTH: 0.670751
G1 F3000
G1 X121.319 Y126.273 E.19505
G1 X122.077 Y122.896 F30000
; LINE_WIDTH: 0.666672
G1 F3000
G1 X120.24 Y121.996 E.19368
G1 X120.236 Y122.002 F30000
; LINE_WIDTH: 0.839626
G1 F2387.949
G1 X122.074 Y122.902 E.25134
G1 X122.061 Y122.925 F30000
; LINE_WIDTH: 1.07974
G1 F1811.057
G2 X121.581 Y122.676 I-5.311 J9.662 E.08769
; LINE_WIDTH: 1.04725
G1 F1872.244
G1 X121.454 Y122.611 E.02231
; LINE_WIDTH: 0.998393
G1 F1972.49
G1 X121.328 Y122.545 E.02118
; LINE_WIDTH: 0.973962
G1 F2026.75
G1 X120.233 Y122.009 E.1765
; WIPE_START
G1 F24000
G1 X121.328 Y122.545 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.269 Y118.66 Z8.8 F30000
G1 Z8.4
G1 E3 F1800
; LINE_WIDTH: 0.973954
G1 F2026.768
G1 X123.95 Y119.672 E.1765
; LINE_WIDTH: 0.998388
G1 F1972.501
G1 X124.026 Y119.792 E.02118
; LINE_WIDTH: 1.04725
G1 F1872.243
G1 X124.103 Y119.912 E.02231
; LINE_WIDTH: 1.07973
G1 F1811.063
G3 X124.394 Y120.368 I-9.148 J6.173 E.08768
G1 X124.416 Y120.354 F30000
; LINE_WIDTH: 0.839629
G1 F2387.937
G1 X123.275 Y118.656 E.25134
G1 X123.281 Y118.652 F30000
; LINE_WIDTH: 0.666684
G1 F3000
G1 X124.423 Y120.35 E.19368
G1 X127.697 Y119.32 F30000
; LINE_WIDTH: 1.08106
G1 F1808.639
G2 X127.669 Y118.779 I-14.753 J.493 E.08781
; LINE_WIDTH: 1.04725
G1 F1872.243
G1 X127.663 Y118.637 E.02232
; LINE_WIDTH: 0.998385
G1 F1972.508
G1 X127.656 Y118.494 E.02118
; LINE_WIDTH: 0.973949
G1 F2026.781
G1 X127.573 Y117.278 E.17649
G1 X127.586 Y117.277 F30000
; LINE_WIDTH: 0.836358
G1 F2398.345
G1 X127.712 Y119.319 E.25021
G1 X131.104 Y120.077 F30000
; LINE_WIDTH: 0.650182
G1 F3000
G1 X132.004 Y118.24 E.18818
G1 X131.998 Y118.236 F30000
; LINE_WIDTH: 0.821315
G1 F2447.399
G1 X131.098 Y120.074 E.24524
G1 X131.075 Y120.061 F30000
; LINE_WIDTH: 1.07668
G1 F1816.645
G2 X131.324 Y119.581 I-9.665 J-5.313 E.08742
; LINE_WIDTH: 1.04725
G1 F1872.244
G1 X131.389 Y119.454 E.02231
; LINE_WIDTH: 0.998392
M73 P90 R1
G1 F1972.492
G1 X131.455 Y119.328 E.02118
; LINE_WIDTH: 0.968705
G1 F2038.818
G1 X131.991 Y118.233 E.17546
; WIPE_START
G1 F24000
G1 X131.455 Y119.328 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X135.34 Y121.269 Z8.8 F30000
G1 Z8.4
G1 E3 F1800
; LINE_WIDTH: 0.968702
G1 F2038.826
G1 X134.328 Y121.95 E.17545
; LINE_WIDTH: 0.998389
G1 F1972.499
G1 X134.208 Y122.026 E.02118
; LINE_WIDTH: 1.04725
G1 F1872.246
G1 X134.088 Y122.103 E.02231
; LINE_WIDTH: 1.07668
G1 F1816.645
G3 X133.632 Y122.394 I-6.169 J-9.14 E.08742
G1 X133.646 Y122.416 F30000
; LINE_WIDTH: 0.821311
G1 F2447.413
G1 X135.344 Y121.275 E.24523
G1 X135.348 Y121.281 F30000
; LINE_WIDTH: 0.650164
G1 F3000
G1 X133.65 Y122.423 E.18817
G1 X134.681 Y125.727 F30000
; LINE_WIDTH: 0.650156
G1 F3000
G1 X136.723 Y125.587 E.18817
G1 X136.723 Y125.587 F30000
; LINE_WIDTH: 0.978632
G1 F2016.148
G1 X136.038 Y125.625 E.09973
; LINE_WIDTH: 1.01145
G1 F1944.658
G1 X135.354 Y125.664 E.1034
; LINE_WIDTH: 1.04906
G1 F1868.728
G1 X135.221 Y125.668 E.02087
; LINE_WIDTH: 1.07026
G1 F1828.485
G1 X134.68 Y125.699 E.08688
G1 X132.209 Y124.701 F30000
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.881008
G1 F2263.676
G1 X132.209 Y127.378 E.3469
G1 X132.637 Y127.614 E.06336
G1 X132.788 Y127.051 E.0756
G1 X132.998 Y125.88 E.15416
G1 X132.991 Y125.707 E.0224
G1 X132.672 Y124.515 E.15983
G1 X132.326 Y124.725 E.05236
G1 X132.519 Y123.688 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 0.718734
G1 F2844.081
G1 X132.261 Y123.299 E.04818
; LINE_WIDTH: 0.669825
G1 F3000
G1 X132.003 Y122.91 E.04446
G2 X131.191 Y122.142 I-10.23 J10.001 E.10638
; LINE_WIDTH: 0.688416
G1 F2987.178
G2 X130.765 Y121.807 I-6.411 J7.708 E.0532
; LINE_WIDTH: 0.726259
G1 F2810.663
G1 X130.558 Y121.66 E.0265
; LINE_WIDTH: 0.770167
G1 F2630.324
G1 X130.313 Y121.499 E.03265
; LINE_WIDTH: 0.760641
G1 F2667.456
G1 X130.073 Y121.413 E.02802
; LINE_WIDTH: 0.718766
G1 F2843.939
G2 X129.802 Y121.316 I-1.938 J4.984 E.02971
; LINE_WIDTH: 0.685512
G1 F3000
G2 X128.219 Y120.977 I-2.299 J6.883 E.15853
; LINE_WIDTH: 0.734301
G1 F2775.807
G1 X128.006 Y120.959 E.02265
; LINE_WIDTH: 0.774556
G1 F2613.561
G2 X127.675 Y120.958 I-.169 J.851 E.03741
; LINE_WIDTH: 0.747035
G1 F2722.346
G1 X127.424 Y121.005 E.02744
; LINE_WIDTH: 0.709446
G1 F2886.443
G2 X127.142 Y121.058 I.853 J5.269 E.02921
; LINE_WIDTH: 0.685983
G1 F2999.291
G2 X125.638 Y121.559 I1.531 J7.116 E.15536
; LINE_WIDTH: 0.723489
G1 F2822.873
G1 X125.606 Y121.573 E.00358
; LINE_WIDTH: 0.742974
G1 F2739.171
G1 X125.449 Y121.648 E.0187
; LINE_WIDTH: 0.774083
G1 F2615.359
G2 X125.136 Y121.846 I.48 J1.104 E.04169
; LINE_WIDTH: 0.734668
G1 F2774.237
G1 X124.944 Y122.013 E.02692
; LINE_WIDTH: 0.683884
G1 F3000
G2 X123.993 Y122.992 I3.972 J4.809 E.13326
; LINE_WIDTH: 0.693113
G1 F2964.072
G1 X123.84 Y123.196 E.02518
; LINE_WIDTH: 0.721337
G1 F2832.434
G2 X123.667 Y123.427 I4.207 J3.324 E.02999
; LINE_WIDTH: 0.752292
G1 F2700.873
G1 X123.592 Y123.539 E.01464
; LINE_WIDTH: 0.773178
G1 F2618.802
G2 X123.428 Y123.876 I.694 J.547 E.04224
; LINE_WIDTH: 0.740127
G1 F2751.089
G1 X123.416 Y123.909 E.00377
; LINE_WIDTH: 0.723557
G1 F2822.571
G1 X123.335 Y124.15 E.02644
; LINE_WIDTH: 0.6824
G1 F3000
G2 X123.015 Y125.476 I5.755 J2.09 E.13292
; LINE_WIDTH: 0.699879
G1 F2931.415
G1 X122.986 Y125.729 E.02547
; LINE_WIDTH: 0.732422
G1 F2783.875
G2 X122.954 Y126.018 I5.322 J.735 E.0306
; LINE_WIDTH: 0.766429
G1 F2644.771
G2 X122.992 Y126.525 I1.188 J.166 E.0568
; LINE_WIDTH: 0.727949
G1 F2803.268
G1 X122.998 Y126.559 E.00363
; LINE_WIDTH: 0.69089
G1 F2974.966
G2 X123.229 Y127.512 I8.946 J-1.657 E.09669
; LINE_WIDTH: 0.680404
G1 F3000
G1 X123.258 Y127.607 E.00966
G2 X123.451 Y128.112 I36.791 J-13.721 E.0524
; LINE_WIDTH: 0.707885
G1 F2893.685
G1 X123.554 Y128.345 E.02581
; LINE_WIDTH: 0.744763
G1 F2731.733
G2 X123.673 Y128.611 I4.972 J-2.069 E.03128
; LINE_WIDTH: 0.761152
G1 F2665.438
G1 X123.724 Y128.709 E.01214
G1 X123.977 Y129.019 E.04406
; LINE_WIDTH: 0.686143
G1 F2998.49
G2 X125.179 Y130.151 I5.569 J-4.707 E.16195
; LINE_WIDTH: 0.717139
G1 F2851.268
G1 X125.386 Y130.3 E.02621
; LINE_WIDTH: 0.758377
G1 F2676.435
G2 X125.625 Y130.469 I3.25 J-4.32 E.03204
; LINE_WIDTH: 0.786148
G1 F2570.301
G1 X125.65 Y130.485 E.00347
; LINE_WIDTH: 0.769863
G1 F2631.492
G1 X125.875 Y130.569 E.02674
; LINE_WIDTH: 0.726748
G1 F2808.517
G2 X126.132 Y130.662 I1.873 J-4.721 E.02856
; LINE_WIDTH: 0.68512
G1 F3000
G2 X127.711 Y131.015 I2.336 J-6.75 E.15839
; LINE_WIDTH: 0.727185
G1 F2806.604
G1 X127.96 Y131.037 E.02605
; LINE_WIDTH: 0.771018
G1 F2627.058
G1 X128.256 Y131.053 E.0332
; LINE_WIDTH: 0.758958
G1 F2674.125
G1 X128.507 Y131.008 E.02795
; LINE_WIDTH: 0.717595
G1 F2849.21
G2 X128.79 Y130.956 I-.818 J-5.284 E.02964
; LINE_WIDTH: 0.685615
G1 F3000
G2 X130.33 Y130.456 I-1.462 J-7.119 E.15857
; LINE_WIDTH: 0.735296
G1 F2771.553
G1 X130.519 Y130.366 E.02218
; LINE_WIDTH: 0.774712
G1 F2612.97
G2 X130.81 Y130.198 I-.299 J-.85 E.03793
; LINE_WIDTH: 0.745492
G1 F2728.716
G1 X131.003 Y130.032 E.02738
; LINE_WIDTH: 0.708416
G1 F2891.218
G2 X131.221 Y129.844 I-3.373 J-4.129 E.02916
; LINE_WIDTH: 0.67413
G1 F3000
G2 X131.821 Y129.257 I-10.898 J-11.731 E.08053
; LINE_WIDTH: 0.621501
G1 X131.991 Y129.078 E.02154
G1 X132.419 Y128.377 E.0717
G1 X133.923 Y129.104 F30000
; LINE_WIDTH: 0.650159
G1 F3000
G1 X135.76 Y130.004 E.18818
G1 X135.764 Y129.998 F30000
; LINE_WIDTH: 0.821321
G1 F2447.381
G1 X133.926 Y129.098 E.24524
G1 X133.939 Y129.075 F30000
; LINE_WIDTH: 1.07668
G1 F1816.645
G2 X134.419 Y129.324 I5.323 J-9.684 E.08742
; LINE_WIDTH: 1.04726
G1 F1872.242
G1 X134.546 Y129.389 E.02231
; LINE_WIDTH: 0.998389
G1 F1972.498
G1 X134.672 Y129.455 E.02118
; LINE_WIDTH: 0.968705
G1 F2038.818
G1 X135.767 Y129.991 E.17545
; WIPE_START
G1 F24000
G1 X134.672 Y129.455 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X132.731 Y133.34 Z8.8 F30000
G1 Z8.4
G1 E3 F1800
; LINE_WIDTH: 0.968697
G1 F2038.837
G1 X132.05 Y132.328 E.17545
; LINE_WIDTH: 0.998389
G1 F1972.499
G1 X131.974 Y132.208 E.02118
; LINE_WIDTH: 1.04726
G1 F1872.239
G1 X131.897 Y132.088 E.02231
; LINE_WIDTH: 1.07668
G1 F1816.644
G3 X131.606 Y131.632 I9.139 J-6.167 E.08742
G1 X131.584 Y131.646 F30000
; LINE_WIDTH: 0.821313
G1 F2447.408
G1 X132.725 Y133.344 E.24524
G1 X132.719 Y133.348 F30000
; LINE_WIDTH: 0.650164
G1 F3000
G1 X131.577 Y131.65 E.18818
G1 X128.301 Y132.68 F30000
; LINE_WIDTH: 1.0761
G1 F1817.704
G1 X128.332 Y133.221 E.0874
; LINE_WIDTH: 1.04906
G1 F1868.73
G1 X128.336 Y133.354 E.02087
; LINE_WIDTH: 1.01145
G1 F1944.66
G1 X128.375 Y134.038 E.1034
; LINE_WIDTH: 0.995042
G1 F1979.759
G1 X128.413 Y134.723 E.10157
G1 X128.413 Y134.723 F30000
; LINE_WIDTH: 0.670739
G1 F3000
G1 X128.273 Y132.681 E.19504
G1 X124.896 Y131.923 F30000
; LINE_WIDTH: 0.666674
G1 F3000
G1 X123.996 Y133.76 E.19368
G1 X124.002 Y133.764 F30000
; LINE_WIDTH: 0.839618
G1 F2387.973
G1 X124.902 Y131.926 E.25134
G1 X124.925 Y131.939 F30000
; LINE_WIDTH: 1.07974
G1 F1811.055
G2 X124.676 Y132.419 I9.686 J5.324 E.08769
; LINE_WIDTH: 1.04726
G1 F1872.239
G1 X124.611 Y132.545 E.02231
; LINE_WIDTH: 0.998398
G1 F1972.479
G1 X124.545 Y132.672 E.02118
; LINE_WIDTH: 0.973969
G1 F2026.735
G1 X124.009 Y133.767 E.1765
; CHANGE_LAYER
; Z_HEIGHT: 8.8
; LAYER_HEIGHT: 0.400001
; WIPE_START
G1 F24000
G1 X124.545 Y132.672 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 22/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L22
M991 S0 P21 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z8.8 I.989 J.709 P1  F30000
G1 X131.343 Y123.182 Z8.8
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2451.784
G1 X131.444 Y123.276 E.01645
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X127.894 Y121.661 I-2.779 J-3.338 E1.98038
G3 X130.78 Y122.66 I.096 J4.392 E.37319
G1 X131.255 Y123.101 E.07758
G1 X130.71 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X127.899 Y122.395 I-2.309 J-2.773 E1.64382
G1 X128.17 Y122.393 E.03237
G3 X130.627 Y123.509 I-.217 J3.743 E.33037
M204 S10000
; WIPE_START
G1 F24000
G1 X130.661 Y125.509 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.954 Y129.151 Z9.2 F30000
G1 X122.852 Y129.749 Z9.2
G1 Z8.8
G1 E3 F1800
; FEATURE: Inner wall
G1 F2451.784
G1 X122.622 Y129.41 E.04903
G1 X123.097 Y129.035 E.07249
G3 X122.319 Y126.673 I13.039 J-5.606 E.29793
G1 X121.667 Y126.673 E.07801
G1 X121.637 Y126.264 E.04903
G1 X122.237 Y126.177 E.07249
G3 X122.744 Y123.742 I14.09 J1.664 E.29793
G1 X122.179 Y123.416 E.07801
G1 X122.358 Y123.047 E.04903
G1 X122.921 Y123.272 E.07249
G3 X124.577 Y121.417 I11.37 J8.485 E.29793
G1 X124.251 Y120.852 E.07801
G1 X124.59 Y120.622 E.04903
G1 X124.965 Y121.097 E.07249
G3 X127.327 Y120.319 I5.605 J13.038 E.29793
M73 P90 R0
G1 X127.327 Y119.667 E.07801
G1 X127.736 Y119.637 E.04903
G1 X127.823 Y120.237 E.07249
G3 X130.258 Y120.744 I-1.664 J14.09 E.29793
G1 X130.584 Y120.179 E.07801
G1 X130.953 Y120.358 E.04903
G1 X130.728 Y120.921 E.07249
G3 X132.583 Y122.577 I-8.485 J11.37 E.29793
G1 X133.148 Y122.251 E.07801
G1 X133.378 Y122.59 E.04903
G1 X132.903 Y122.965 E.07249
G3 X133.681 Y125.327 I-13.039 J5.606 E.29793
G1 X134.333 Y125.327 E.07801
G1 X134.363 Y125.736 E.04903
G1 X133.763 Y125.823 E.07249
G3 X133.256 Y128.258 I-14.09 J-1.664 E.29793
G1 X133.821 Y128.584 E.07801
G1 X133.642 Y128.953 E.04903
G1 X133.079 Y128.728 E.07249
G3 X131.423 Y130.583 I-11.364 J-8.481 E.29793
G1 X131.749 Y131.148 E.07802
G1 X131.41 Y131.378 E.04903
G1 X131.035 Y130.903 E.07249
G3 X128.673 Y131.681 I-5.605 J-13.037 E.29793
G1 X128.673 Y132.333 E.07801
G1 X128.264 Y132.363 E.04903
G1 X128.177 Y131.763 E.07249
G3 X125.742 Y131.256 I1.664 J-14.09 E.29793
G1 X125.416 Y131.821 E.07801
G1 X125.047 Y131.642 E.04903
G1 X125.272 Y131.079 E.07249
G3 X123.417 Y129.423 I8.481 J-11.364 E.29792
G1 X122.956 Y129.689 E.06366
G1 X123.219 Y130.385 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G3 X120.677 Y131.403 I-4.053 J-6.436 E.32936
G3 X120.583 Y131.272 I1.461 J-1.149 E.01939
G3 X120.283 Y130.822 I5.005 J-3.659 E.06473
G3 X122.218 Y128.793 I6.446 J4.213 E.33732
G3 X121.751 Y127.407 I9.979 J-4.134 E.17517
G1 X121.667 Y127.407 E.01012
G3 X118.957 Y127.018 I-.292 J-7.601 E.32936
G3 X118.941 Y126.857 I1.841 J-.265 E.01939
G3 X118.906 Y126.317 I6.164 J-.666 E.06473
G3 X121.596 Y125.528 I3.37 J6.51 E.33752
G3 X121.885 Y124.094 I10.707 J1.409 E.17517
G1 X121.812 Y124.052 E.01012
G3 X119.659 Y122.36 I3.547 J-6.728 E.32936
G3 X119.726 Y122.212 I1.725 J.691 E.01939
G3 X119.966 Y121.728 I5.671 J2.505 E.06473
G3 X122.69 Y122.39 I-.425 J7.688 E.33733
G3 X123.657 Y121.292 I8.567 J6.572 E.17517
G1 X123.615 Y121.219 E.01012
G3 X122.597 Y118.677 I6.436 J-4.053 E.32936
G3 X122.728 Y118.583 I1.149 J1.461 E.01939
G3 X123.178 Y118.283 I3.659 J5.005 E.06473
G3 X125.207 Y120.218 I-4.213 J6.446 E.33732
G3 X126.593 Y119.751 I4.134 J9.979 E.17517
G1 X126.593 Y119.667 E.01012
G3 X126.982 Y116.957 I7.601 J-.292 E.32936
G3 X127.143 Y116.941 I.265 J1.84 E.01939
G3 X127.683 Y116.907 I.638 J5.843 E.06476
G3 X128.472 Y119.596 I-6.511 J3.369 E.33744
G3 X129.906 Y119.885 I-1.409 J10.707 E.17517
G1 X129.948 Y119.812 E.01012
G3 X131.64 Y117.659 I6.728 J3.547 E.32936
G3 X131.788 Y117.726 I-.691 J1.726 E.01939
G3 X132.272 Y117.966 I-2.505 J5.671 E.06473
G3 X131.61 Y120.69 I-7.688 J-.425 E.33733
G3 X132.708 Y121.657 I-6.573 J8.567 E.17517
G1 X132.781 Y121.615 E.01012
G3 X135.323 Y120.597 I4.053 J6.436 E.32936
G3 X135.417 Y120.728 I-1.461 J1.149 E.01939
G3 X135.717 Y121.178 I-5.005 J3.658 E.06473
G3 X133.782 Y123.207 I-6.446 J-4.213 E.33732
G3 X134.249 Y124.593 I-9.98 J4.134 E.17517
G1 X134.333 Y124.593 E.01012
G3 X137.043 Y124.982 I.292 J7.601 E.32936
G3 X137.059 Y125.143 I-1.841 J.265 E.01939
G3 X137.094 Y125.683 I-6.164 J.666 E.06473
G3 X134.404 Y126.472 I-3.37 J-6.51 E.33752
G3 X134.115 Y127.906 I-10.707 J-1.409 E.17517
G1 X134.188 Y127.948 E.01012
G3 X136.341 Y129.64 I-3.547 J6.728 E.32936
G3 X136.274 Y129.788 I-1.726 J-.691 E.01939
G3 X136.034 Y130.272 I-5.671 J-2.506 E.06473
M73 P91 R0
G3 X133.31 Y129.61 I.425 J-7.688 E.33733
G3 X132.343 Y130.708 I-8.563 J-6.569 E.17517
G1 X132.385 Y130.781 E.01013
G3 X133.403 Y133.323 I-6.436 J4.053 E.32936
G3 X133.272 Y133.417 I-1.149 J-1.461 E.01939
G3 X132.822 Y133.717 I-3.659 J-5.006 E.06473
G3 X130.793 Y131.782 I4.213 J-6.446 E.33732
G3 X129.407 Y132.249 I-4.134 J-9.978 E.17517
G1 X129.407 Y132.333 E.01012
G3 X129.018 Y135.043 I-7.601 J.292 E.32936
G3 X128.857 Y135.059 I-.265 J-1.84 E.01939
G3 X128.317 Y135.094 I-.666 J-6.164 E.06473
G3 X127.528 Y132.404 I6.51 J-3.37 E.33752
G3 X126.094 Y132.115 I1.409 J-10.706 E.17517
G1 X126.052 Y132.188 E.01012
G3 X124.36 Y134.341 I-6.728 J-3.547 E.32936
G3 X124.212 Y134.274 I.691 J-1.725 E.01939
G3 X123.728 Y134.034 I2.505 J-5.671 E.06473
G3 X124.39 Y131.31 I7.688 J.425 E.33733
G3 X123.317 Y130.368 I6.569 J-8.563 E.17093
M204 S10000
; WIPE_START
G1 F24000
G1 X122.706 Y130.681 E-.97894
G1 X122.077 Y130.984 E-.99405
G1 X121.498 Y131.194 E-.87702
; WIPE_END
G1 E-.15 F1800
G1 X122.419 Y129.765 Z9.2 F30000
G1 Z8.8
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 0.839766
G1 F2387.505
G1 X120.79 Y130.927 E.24586
G1 X120.786 Y130.921 F30000
; LINE_WIDTH: 0.66681
G1 F3000
G1 X122.415 Y129.759 E.18947
G1 X122.022 Y130.065 F30000
; LINE_WIDTH: 1.06085
G1 F1846.133
G1 X122.099 Y129.356 E.11341
G1 X122.022 Y130.065 F30000
; LINE_WIDTH: 1.04741
G1 F1871.949
G1 X121.904 Y130.145 E.02232
; LINE_WIDTH: 0.998534
G1 F1972.184
G1 X121.786 Y130.225 E.02119
; LINE_WIDTH: 0.974098
G1 F2026.44
G1 X120.794 Y130.933 E.17645
G1 X123.681 Y128.606 F30000
; LINE_WIDTH: 0.755522
G1 F2687.847
G1 X123.753 Y128.744 E.01699
G1 X123.977 Y129.018 E.03874
; LINE_WIDTH: 0.6868
G1 F2995.211
G2 X124.661 Y129.722 I4.971 J-4.147 E.09623
; LINE_WIDTH: 0.675649
G1 F3000
G1 X124.797 Y129.841 E.01736
G2 X125.182 Y130.147 I10.169 J-12.388 E.04722
; LINE_WIDTH: 0.704899
G1 F2907.643
G1 X125.39 Y130.294 E.02569
; LINE_WIDTH: 0.741662
G1 F2744.651
G2 X125.629 Y130.46 I3.203 J-4.329 E.03112
; LINE_WIDTH: 0.772251
G1 F2622.337
G1 X125.693 Y130.501 E.00852
; LINE_WIDTH: 0.763179
G1 F2657.463
G1 X125.897 Y130.576 E.02396
; LINE_WIDTH: 0.723922
G1 F2820.956
G2 X126.132 Y130.662 I1.714 J-4.326 E.02606
; LINE_WIDTH: 0.680708
G1 F3000
G2 X127.711 Y131.009 I2.277 J-6.592 E.15712
; LINE_WIDTH: 0.714134
G1 F2864.906
G1 X127.965 Y131.03 E.02609
; LINE_WIDTH: 0.755237
G1 F2688.992
G2 X128.256 Y131.052 I.318 J-2.251 E.03188
; LINE_WIDTH: 0.75806
G1 F2677.696
G1 X128.507 Y131.007 E.02791
; LINE_WIDTH: 0.716698
G1 F2853.26
G2 X128.79 Y130.956 I-.818 J-5.286 E.0296
; LINE_WIDTH: 0.68066
G1 F3000
G2 X130.327 Y130.45 I-1.468 J-7.052 E.15712
; LINE_WIDTH: 0.722709
G1 F2826.328
G1 X130.536 Y130.35 E.02407
; LINE_WIDTH: 0.76361
G1 F2655.771
G2 X130.81 Y130.197 I-.232 J-.74 E.03487
; LINE_WIDTH: 0.744531
G1 F2732.695
G1 X131.003 Y130.032 E.02734
; LINE_WIDTH: 0.707473
G1 F2895.603
G2 X131.221 Y129.844 I-3.376 J-4.133 E.02911
; LINE_WIDTH: 0.672722
G1 F3000
G2 X131.796 Y129.279 I-11.645 J-12.431 E.0771
; LINE_WIDTH: 0.625552
G1 X131.855 Y129.215 E.00769
G2 X131.989 Y129.076 I-2.694 J-2.738 E.01699
; LINE_WIDTH: 0.624617
G1 X132.2 Y128.724 E.03602
; LINE_WIDTH: 0.640269
G1 X132.411 Y128.372 E.03707
G1 X134.048 Y128.957 F30000
; LINE_WIDTH: 0.65029
G1 F3000
G1 X135.869 Y129.787 E.18409
G1 X135.872 Y129.781 F30000
; LINE_WIDTH: 0.821443
G1 F2446.973
G1 X134.051 Y128.95 E.23989
G1 X133.857 Y129.433 F30000
; LINE_WIDTH: 1.06457
G1 F1839.119
G1 X134.506 Y129.143 E.11347
G1 X134.637 Y129.206 E.02327
; LINE_WIDTH: 0.998538
G1 F1972.177
G1 X134.766 Y129.269 E.02118
; LINE_WIDTH: 0.968846
G1 F2038.492
G1 X135.875 Y129.774 E.17541
; WIPE_START
G1 F24000
G1 X134.766 Y129.269 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X134.783 Y126.046 Z9.2 F30000
G1 Z8.8
G1 E3 F1800
; LINE_WIDTH: 1.06695
G1 F1834.655
G1 X135.206 Y125.469 E.11439
G1 X135.334 Y125.46 E.02056
; LINE_WIDTH: 1.01372
G1 F1939.905
G1 X136.021 Y125.403 E.10422
; LINE_WIDTH: 0.979478
G1 F2014.241
G1 X136.708 Y125.345 E.10037
; WIPE_START
G1 F24000
G1 X136.021 Y125.403 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X133.901 Y122.644 Z9.2 F30000
G1 Z8.8
G1 E3 F1800
; LINE_WIDTH: 1.06457
G1 F1839.125
G1 X133.975 Y121.937 E.11347
G1 X134.096 Y121.855 E.02327
; LINE_WIDTH: 0.998536
G1 F1972.181
G1 X134.214 Y121.775 E.02118
; LINE_WIDTH: 0.968842
G1 F2038.502
G1 X135.206 Y121.067 E.17541
G1 X135.21 Y121.073 F30000
; LINE_WIDTH: 0.821461
G1 F2446.915
G1 X133.581 Y122.235 E.2399
G1 X133.585 Y122.241 F30000
; LINE_WIDTH: 0.650273
G1 F3000
G1 X135.214 Y121.079 E.18408
G1 X132.268 Y123.31 F30000
; LINE_WIDTH: 0.717714
G1 F2848.673
G1 X132.534 Y123.71 E.04944
G1 X132.268 Y123.31 F30000
; LINE_WIDTH: 0.671012
G1 F3000
G1 X132.002 Y122.91 E.04579
G2 X130.762 Y121.812 I-6.743 J6.363 E.15819
; LINE_WIDTH: 0.712964
G1 F2870.25
G1 X130.553 Y121.666 E.02604
; LINE_WIDTH: 0.754038
G1 F2693.816
G2 X130.307 Y121.498 I-2.793 J3.802 E.03243
; LINE_WIDTH: 0.759055
G1 F2673.738
G1 X130.071 Y121.412 E.02764
; LINE_WIDTH: 0.717631
G1 F2849.047
G2 X129.802 Y121.316 I-1.92 J4.936 E.02935
; LINE_WIDTH: 0.680621
G1 F3000
G2 X128.219 Y120.983 I-2.258 J6.815 E.15711
; LINE_WIDTH: 0.721817
G1 F2830.294
G1 X127.983 Y120.966 E.02454
; LINE_WIDTH: 0.76314
G1 F2657.615
G2 X127.675 Y120.959 I-.171 J.725 E.03433
; LINE_WIDTH: 0.746138
G1 F2726.045
G1 X127.424 Y121.005 E.02741
; LINE_WIDTH: 0.708549
G1 F2890.598
G2 X127.142 Y121.059 I.853 J5.269 E.02916
; LINE_WIDTH: 0.681287
G1 F3000
G1 X126.648 Y121.179 E.04936
G2 X125.61 Y121.579 I3.135 J9.685 E.10799
; LINE_WIDTH: 0.729692
G1 F2795.676
G1 X125.433 Y121.666 E.02068
; LINE_WIDTH: 0.765171
G1 F2649.667
G2 X125.136 Y121.847 I.383 J.959 E.03866
; LINE_WIDTH: 0.733762
G1 F2778.114
G1 X124.944 Y122.014 E.02688
; LINE_WIDTH: 0.687311
G1 F2992.666
G2 X124.366 Y122.559 I6.724 J7.716 E.07792
; LINE_WIDTH: 0.68291
G1 F3000
G1 X124.266 Y122.674 E.01482
G2 X123.693 Y123.403 I6.191 J5.459 E.09025
; LINE_WIDTH: 0.720438
G1 F2836.446
G1 X123.674 Y123.431 E.00355
; LINE_WIDTH: 0.7382
G1 F2759.214
G1 X123.587 Y123.562 E.01674
; LINE_WIDTH: 0.763293
G1 F2657.014
G2 X123.416 Y123.909 I1.202 J.808 E.04281
; LINE_WIDTH: 0.722645
G1 F2826.616
G1 X123.335 Y124.15 E.02641
; LINE_WIDTH: 0.67884
G1 F3000
G2 X123.019 Y125.477 I6.262 J2.195 E.13201
; LINE_WIDTH: 0.690198
G1 F2978.371
G1 X122.992 Y125.73 E.02506
; LINE_WIDTH: 0.718315
G1 F2845.965
G2 X122.962 Y126.017 I5.308 J.69 E.02983
; LINE_WIDTH: 0.758322
G1 F2676.655
G2 X122.993 Y126.525 I1.232 J.181 E.05608
; LINE_WIDTH: 0.727061
G1 F2807.147
G1 X122.999 Y126.559 E.00362
; LINE_WIDTH: 0.6926
G1 F2966.579
G2 X123.182 Y127.351 I7.762 J-1.376 E.08047
; LINE_WIDTH: 0.673817
G1 F3000
G1 X123.262 Y127.606 E.02552
G2 X123.455 Y128.11 I21.391 J-7.906 E.05177
; LINE_WIDTH: 0.696931
G1 F2945.556
G1 X123.56 Y128.342 E.02535
; LINE_WIDTH: 0.729361
G1 F2797.116
G2 X123.681 Y128.606 I4.941 J-2.102 E.03044
G1 X124.567 Y131.857 F30000
; LINE_WIDTH: 1.06089
G1 F1846.056
G1 X124.856 Y132.509 E.11341
; LINE_WIDTH: 1.0474
G1 F1871.957
G1 X124.794 Y132.637 E.02232
; LINE_WIDTH: 0.998536
G1 F1972.181
G1 X124.731 Y132.766 E.02118
; LINE_WIDTH: 0.974102
G1 F2026.43
G1 X124.226 Y133.875 E.17645
G1 X124.219 Y133.872 F30000
; LINE_WIDTH: 0.839769
G1 F2387.496
G1 X125.05 Y132.051 E.24587
G1 X125.043 Y132.048 F30000
; LINE_WIDTH: 0.666805
G1 F3000
G1 X124.213 Y133.869 E.18947
; WIPE_START
G1 F24000
G1 X125.042 Y132.049 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X127.954 Y132.783 Z9.2 F30000
G1 Z8.8
G1 E3 F1800
; LINE_WIDTH: 1.06533
G1 F1837.685
G1 X128.531 Y133.206 E.11419
G1 X128.54 Y133.334 E.02053
; LINE_WIDTH: 1.01372
G1 F1939.909
G1 X128.597 Y134.021 E.10422
; LINE_WIDTH: 0.996598
G1 F1976.378
G1 X128.655 Y134.708 E.10229
; WIPE_START
G1 F24000
G1 X128.597 Y134.021 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X131.356 Y131.901 Z9.2 F30000
G1 Z8.8
G1 E3 F1800
; LINE_WIDTH: 1.06457
G1 F1839.124
G1 X132.063 Y131.975 E.11347
G1 X132.145 Y132.096 E.02327
; LINE_WIDTH: 0.998534
G1 F1972.186
G1 X132.225 Y132.214 E.02119
; LINE_WIDTH: 0.968841
G1 F2038.505
G1 X132.933 Y133.206 E.17541
G1 X132.927 Y133.21 F30000
; LINE_WIDTH: 0.82146
G1 F2446.917
G1 X131.765 Y131.581 E.2399
G1 X131.759 Y131.585 F30000
; LINE_WIDTH: 0.650282
G1 F3000
G1 X132.921 Y133.214 E.18408
G1 X132.206 Y125.769 F30000
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.857771
G1 F2331.818
G1 X132.188 Y126.214 E.05603
; LINE_WIDTH: 0.808129
G1 F2492.079
G2 X132.171 Y127.4 I15.072 J.816 E.13968
G1 X132.663 Y127.676 E.06637
G1 X132.884 Y126.728 E.11461
; LINE_WIDTH: 0.822769
G1 F2442.572
G1 X132.937 Y126.279 E.05423
; LINE_WIDTH: 0.870419
G1 F2294.225
G1 X132.991 Y125.831 E.05774
G1 X132.983 Y125.67 E.02059
G1 X132.673 Y124.532 E.15084
G1 X132.344 Y124.751 E.05062
G1 X132.206 Y124.721 E.01799
G1 X132.206 Y125.649 E.11863
G1 X131.433 Y120.143 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 1.06457
G1 F1839.125
G1 X131.143 Y119.494 E.11347
G1 X131.206 Y119.363 E.02327
; LINE_WIDTH: 0.998537
G1 F1972.178
G1 X131.269 Y119.234 E.02119
; LINE_WIDTH: 0.968843
G1 F2038.499
G1 X131.774 Y118.125 E.17541
G1 X131.781 Y118.128 F30000
; LINE_WIDTH: 0.821442
G1 F2446.979
G1 X130.95 Y119.949 E.23989
G1 X130.957 Y119.952 F30000
; LINE_WIDTH: 0.650297
G1 F3000
G1 X131.787 Y118.131 E.18409
; WIPE_START
G1 F24000
G1 X130.958 Y119.951 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X128.046 Y119.217 Z9.2 F30000
G1 Z8.8
G1 E3 F1800
; LINE_WIDTH: 1.06532
G1 F1837.708
G1 X127.469 Y118.794 E.11419
G1 X127.46 Y118.666 E.02053
; LINE_WIDTH: 1.01372
G1 F1939.909
G1 X127.403 Y117.979 E.10422
; LINE_WIDTH: 0.996598
G1 F1976.378
G1 X127.345 Y117.292 E.10229
; WIPE_START
G1 F24000
G1 X127.403 Y117.979 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X124.644 Y120.099 Z9.2 F30000
G1 Z8.8
G1 E3 F1800
; LINE_WIDTH: 1.06086
G1 F1846.108
G1 X123.935 Y120.022 E.11341
; LINE_WIDTH: 1.04741
G1 F1871.947
G1 X123.855 Y119.904 E.02232
; LINE_WIDTH: 0.998537
G1 F1972.179
G1 X123.775 Y119.786 E.02118
; LINE_WIDTH: 0.974103
G1 F2026.429
G1 X123.067 Y118.794 E.17645
G1 X123.073 Y118.79 F30000
; LINE_WIDTH: 0.839759
G1 F2387.528
G1 X124.235 Y120.419 E.24586
G1 X124.241 Y120.415 F30000
; LINE_WIDTH: 0.666807
G1 F3000
G1 X123.079 Y118.786 E.18947
; WIPE_START
G1 F24000
G1 X124.241 Y120.414 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X122.143 Y122.567 Z9.2 F30000
G1 Z8.8
G1 E3 F1800
; LINE_WIDTH: 1.06088
G1 F1846.085
G1 X121.491 Y122.856 E.11341
; LINE_WIDTH: 1.04741
G1 F1871.948
G1 X121.363 Y122.794 E.02232
; LINE_WIDTH: 0.998536
G1 F1972.18
G1 X121.234 Y122.731 E.02119
; LINE_WIDTH: 0.974101
G1 F2026.433
G1 X120.125 Y122.226 E.17645
G1 X120.128 Y122.219 F30000
; LINE_WIDTH: 0.839775
G1 F2387.475
G1 X121.949 Y123.05 E.24587
G1 X121.952 Y123.043 F30000
; LINE_WIDTH: 0.666804
G1 F3000
G1 X120.131 Y122.213 E.18947
; WIPE_START
G1 F24000
G1 X121.951 Y123.042 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X121.217 Y125.954 Z9.2 F30000
G1 Z8.8
G1 E3 F1800
; LINE_WIDTH: 1.06532
G1 F1837.709
G1 X120.794 Y126.531 E.11418
G1 X120.665 Y126.54 E.02053
; LINE_WIDTH: 1.01372
G1 F1939.914
G1 X119.979 Y126.597 E.10421
; LINE_WIDTH: 0.996598
G1 F1976.378
G1 X119.292 Y126.655 E.10229
; CHANGE_LAYER
; Z_HEIGHT: 9.2
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X119.979 Y126.597 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 23/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L23
M991 S0 P22 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
M73 P92 R0
G3 Z9.2 I.35 J1.165 P1  F30000
G1 X131.343 Y123.182 Z9.2
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2406
G1 X131.444 Y123.276 E.01647
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X127.867 Y121.661 I-2.777 J-3.339 E1.97634
G3 X130.78 Y122.66 I.122 J4.395 E.3765
G1 X131.255 Y123.101 E.07756
G1 X130.71 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2406
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X127.872 Y122.395 I-2.307 J-2.774 E1.63993
G1 X128.17 Y122.393 E.03567
G3 X130.627 Y123.509 I-.217 J3.743 E.33037
M204 S10000
; WIPE_START
G1 F24000
G1 X130.661 Y125.509 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X124.022 Y129.275 Z9.6 F30000
G1 X123.029 Y129.838 Z9.6
G1 Z9.2
G1 E3 F1800
; FEATURE: Inner wall
G1 F2406
G1 X122.783 Y129.504 E.04959
G1 X123.206 Y129.151 E.06591
G3 X122.299 Y126.811 I13.074 J-6.413 E.30058
G1 X121.776 Y126.838 E.0626
G1 X121.73 Y126.426 E.04959
G1 X122.272 Y126.331 E.0659
G3 X122.657 Y123.852 I14.533 J.984 E.30058
G1 X122.191 Y123.614 E.06259
G1 X122.357 Y123.234 E.04959
G1 X122.874 Y123.423 E.0659
G3 X124.447 Y121.468 I12.093 J8.117 E.30058
G1 X124.162 Y121.029 E.06261
G1 X124.496 Y120.783 E.04959
G1 X124.849 Y121.206 E.06591
G3 X127.189 Y120.299 I6.415 J13.078 E.30058
G1 X127.162 Y119.776 E.0626
G1 X127.574 Y119.73 E.04959
G1 X127.669 Y120.272 E.0659
G3 X130.148 Y120.657 I-.984 J14.533 E.30058
G1 X130.386 Y120.191 E.06259
G1 X130.766 Y120.357 E.04959
G1 X130.577 Y120.874 E.0659
G3 X132.532 Y122.447 I-8.117 J12.093 E.30058
G1 X132.971 Y122.162 E.0626
G1 X133.217 Y122.496 E.04959
G1 X132.794 Y122.849 E.0659
G3 X133.701 Y125.189 I-13.078 J6.415 E.30058
G1 X134.224 Y125.162 E.0626
G1 X134.27 Y125.574 E.04959
G1 X133.728 Y125.669 E.0659
G3 X133.343 Y128.148 I-14.533 J-.984 E.30058
G1 X133.809 Y128.386 E.06259
G1 X133.643 Y128.766 E.04959
G1 X133.126 Y128.577 E.0659
G3 X131.553 Y130.532 I-12.093 J-8.117 E.30058
G1 X131.838 Y130.971 E.0626
G1 X131.504 Y131.217 E.04959
G1 X131.151 Y130.794 E.0659
G3 X128.811 Y131.701 I-6.413 J-13.074 E.30058
G1 X128.838 Y132.224 E.0626
G1 X128.426 Y132.27 E.04959
G1 X128.331 Y131.728 E.0659
G3 X125.852 Y131.343 I.984 J-14.533 E.30058
G1 X125.614 Y131.809 E.06259
G1 X125.234 Y131.643 E.04959
G1 X125.423 Y131.126 E.0659
G3 X123.468 Y129.553 I8.117 J-12.093 E.30058
G1 X123.13 Y129.772 E.04824
G1 X123.342 Y130.51 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2406
G3 X120.83 Y131.604 I-4.051 J-5.867 E.32991
G1 X120.733 Y131.476 E.0193
G3 X120.419 Y131.037 I4.873 J-3.807 E.06456
G3 X122.306 Y128.946 I6.569 J4.032 E.33887
G3 X121.778 Y127.573 I9.685 J-4.514 E.17613
G1 X121.712 Y127.577 E.00798
G3 X118.989 Y127.268 I-.574 J-7.106 E.32991
G1 X118.968 Y127.108 E.0193
G3 X118.917 Y126.571 I6.122 J-.86 E.06456
G3 X121.596 Y125.704 I3.673 J6.777 E.33887
G3 X121.825 Y124.251 I10.647 J.934 E.17613
G1 X121.766 Y124.221 E.00797
G3 X119.562 Y122.593 I3.056 J-6.442 E.32991
G1 X119.624 Y122.444 E.0193
G3 X119.848 Y121.953 I5.732 J2.316 E.06456
G3 X122.602 Y122.542 I-.207 J7.705 E.33887
G3 X123.527 Y121.398 I8.753 J6.132 E.17613
G1 X123.49 Y121.342 E.00797
G3 X122.396 Y118.83 I5.867 J-4.051 E.32991
G1 X122.524 Y118.733 E.0193
G3 X122.963 Y118.419 I3.807 J4.873 E.06456
G3 X125.054 Y120.306 I-4.032 J6.569 E.33887
G3 X126.427 Y119.778 I4.515 J9.688 E.17613
G1 X126.423 Y119.712 E.00798
G3 X126.732 Y116.989 I7.106 J-.574 E.32991
G1 X126.892 Y116.968 E.0193
G3 X127.429 Y116.917 I.86 J6.123 E.06456
G3 X128.296 Y119.596 I-6.777 J3.673 E.33887
G3 X129.749 Y119.825 I-.934 J10.647 E.17613
G1 X129.779 Y119.766 E.00797
G3 X131.407 Y117.562 I6.442 J3.056 E.32991
G1 X131.556 Y117.624 E.0193
G3 X132.047 Y117.848 I-2.316 J5.733 E.06456
G3 X131.458 Y120.602 I-7.705 J-.207 E.33887
G3 X132.602 Y121.527 I-6.132 J8.753 E.17613
G1 X132.658 Y121.49 E.00797
G3 X135.17 Y120.396 I4.051 J5.867 E.32991
G1 X135.267 Y120.524 E.0193
G3 X135.581 Y120.963 I-4.873 J3.807 E.06456
G3 X133.694 Y123.054 I-6.569 J-4.032 E.33887
G3 X134.222 Y124.427 I-9.688 J4.515 E.17613
G1 X134.288 Y124.423 E.00798
G3 X137.011 Y124.732 I.574 J7.106 E.32991
G1 X137.032 Y124.892 E.0193
G3 X137.083 Y125.429 I-6.123 J.86 E.06456
G3 X134.404 Y126.296 I-3.673 J-6.777 E.33887
G3 X134.175 Y127.749 I-10.647 J-.934 E.17613
G1 X134.234 Y127.779 E.00797
G3 X136.438 Y129.407 I-3.056 J6.442 E.32991
G1 X136.376 Y129.556 E.0193
G3 X136.152 Y130.047 I-5.732 J-2.316 E.06456
G3 X133.398 Y129.458 I.207 J-7.705 E.33887
G3 X132.473 Y130.602 I-8.753 J-6.132 E.17613
G1 X132.51 Y130.658 E.00797
G3 X133.604 Y133.17 I-5.867 J4.051 E.32991
G1 X133.476 Y133.267 E.0193
G3 X133.037 Y133.581 I-3.807 J-4.872 E.06456
G3 X130.946 Y131.694 I4.032 J-6.569 E.33887
G3 X129.573 Y132.222 I-4.514 J-9.686 E.17613
G1 X129.577 Y132.288 E.00798
G3 X129.268 Y135.011 I-7.106 J.574 E.32991
G1 X129.108 Y135.032 E.0193
G3 X128.571 Y135.083 I-.86 J-6.123 E.06456
G3 X127.704 Y132.404 I6.776 J-3.673 E.33887
G3 X126.251 Y132.175 I.934 J-10.647 E.17613
G1 X126.221 Y132.234 E.00797
G3 X124.593 Y134.438 I-6.442 J-3.056 E.32991
G1 X124.444 Y134.376 E.0193
G3 X123.953 Y134.152 I2.316 J-5.733 E.06456
G3 X124.542 Y131.398 I7.705 J.207 E.33887
G3 X123.437 Y130.51 I6.132 J-8.753 E.16974
M204 S10000
; WIPE_START
G1 F24000
G1 X122.84 Y130.825 E-.96221
G1 X122.218 Y131.146 E-.99718
G1 X121.637 Y131.375 E-.8906
; WIPE_END
G1 E-.15 F1800
G1 X122.61 Y129.889 Z9.6 F30000
G1 Z9.2
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 1.08386
G1 F1803.566
G2 X122.138 Y130.229 I6.69 J9.778 E.09468
; LINE_WIDTH: 1.04705
G1 F1872.633
G1 X122.023 Y130.312 E.02231
; LINE_WIDTH: 0.998194
G1 F1972.919
G1 X121.907 Y130.395 E.02117
; LINE_WIDTH: 0.973763
G1 F2027.203
G1 X120.934 Y131.131 E.17652
G1 X120.93 Y131.125 F30000
; LINE_WIDTH: 0.839438
G1 F2388.543
G1 X122.594 Y129.867 E.25626
G1 X121.388 Y126.673 F30000
; LINE_WIDTH: 1.08386
G1 F1803.568
G2 X120.809 Y126.732 I.909 J11.849 E.09468
; LINE_WIDTH: 1.04705
G1 F1872.638
G1 X120.667 Y126.746 E.0223
; LINE_WIDTH: 0.998196
G1 F1972.915
G1 X120.526 Y126.76 E.02117
; LINE_WIDTH: 0.973771
G1 F2027.187
G1 X119.315 Y126.911 E.17652
G1 X119.315 Y126.903 F30000
; LINE_WIDTH: 0.83944
G1 F2388.536
G1 X121.385 Y126.646 E.25626
G1 X121.938 Y123.277 F30000
; LINE_WIDTH: 1.08387
G1 F1803.547
G2 X121.407 Y123.038 I-5.132 J10.703 E.09469
; LINE_WIDTH: 1.04705
G1 F1872.64
G1 X121.277 Y122.98 E.02231
; LINE_WIDTH: 0.998181
G1 F1972.948
G1 X121.147 Y122.921 E.02118
; LINE_WIDTH: 0.973747
G1 F2027.241
M73 P93 R0
G1 X120.023 Y122.446 E.17651
G1 X120.027 Y122.44 F30000
; LINE_WIDTH: 0.839444
G1 F2388.524
G1 X121.948 Y123.252 E.25627
G1 X124.111 Y120.61 F30000
; LINE_WIDTH: 1.08386
G1 F1803.58
G2 X123.771 Y120.138 I-9.791 J6.7 E.09466
; LINE_WIDTH: 1.04706
G1 F1872.626
G1 X123.688 Y120.023 E.02231
; LINE_WIDTH: 0.998191
G1 F1972.927
G1 X123.605 Y119.907 E.02118
; LINE_WIDTH: 0.973755
G1 F2027.222
G1 X122.869 Y118.934 E.17651
G1 X122.875 Y118.93 F30000
; LINE_WIDTH: 0.839456
G1 F2388.486
G1 X124.133 Y120.594 E.25626
G1 X127.327 Y119.388 F30000
; LINE_WIDTH: 1.08386
G1 F1803.568
G2 X127.268 Y118.809 I-11.849 J.909 E.09468
; LINE_WIDTH: 1.04705
G1 F1872.638
G1 X127.254 Y118.667 E.0223
; LINE_WIDTH: 0.998196
G1 F1972.915
G1 X127.24 Y118.526 E.02117
; LINE_WIDTH: 0.973771
G1 F2027.187
G1 X127.089 Y117.315 E.17652
G1 X127.097 Y117.315 F30000
; LINE_WIDTH: 0.839442
G1 F2388.531
G1 X127.354 Y119.385 E.25626
G1 X130.723 Y119.938 F30000
; LINE_WIDTH: 1.07649
G1 F1816.99
G2 X130.962 Y119.407 I-10.698 J-5.13 E.09399
; LINE_WIDTH: 1.04705
G1 F1872.648
G1 X131.02 Y119.277 E.02231
; LINE_WIDTH: 0.998178
G1 F1972.954
G1 X131.079 Y119.147 E.02118
; LINE_WIDTH: 0.968491
G1 F2039.313
G1 X131.554 Y118.022 E.17571
G1 X131.561 Y118.025 F30000
; LINE_WIDTH: 0.821135
G1 F2406
G1 X130.748 Y119.948 E.25024
G1 X133.39 Y122.111 F30000
; LINE_WIDTH: 1.07648
G1 F1817.004
G2 X133.862 Y121.771 I-6.704 J-9.796 E.09398
; LINE_WIDTH: 1.04705
G1 F1872.632
G1 X133.977 Y121.688 E.02231
; LINE_WIDTH: 0.998194
G1 F1972.921
G1 X134.093 Y121.605 E.02117
; LINE_WIDTH: 0.968507
G1 F2039.276
G1 X135.067 Y120.868 E.17572
G1 X135.071 Y120.874 F30000
; LINE_WIDTH: 0.821131
G1 F2406
G1 X133.406 Y122.133 E.25023
G1 X134.615 Y125.354 F30000
; LINE_WIDTH: 0.821132
G1 F2406
G1 X136.685 Y125.097 E.25003
G1 X136.685 Y125.089 F30000
; LINE_WIDTH: 0.968514
G1 F2039.261
G1 X135.474 Y125.24 E.17548
; LINE_WIDTH: 0.9982
G1 F1972.908
G1 X135.333 Y125.254 E.02117
; LINE_WIDTH: 1.04705
G1 F1872.636
G1 X135.191 Y125.268 E.0223
; LINE_WIDTH: 1.07649
G1 F1816.988
G3 X134.612 Y125.327 I-1.487 J-11.784 E.09398
G1 X132.202 Y125.492 F30000
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.849849
G1 F2355.994
G1 X132.185 Y126.116 E.07772
; LINE_WIDTH: 0.802588
G1 F2406
G2 X132.168 Y127.736 I30.037 J1.122 E.18929
G1 X132.656 Y127.892 E.0599
G1 X132.879 Y126.778 E.13278
; LINE_WIDTH: 0.816201
G1 X132.93 Y126.156 E.0743
; LINE_WIDTH: 0.859805
G1 F2325.688
G1 X132.98 Y125.534 E.07873
G1 X132.962 Y125.367 E.02113
G1 X132.644 Y124.422 E.12577
G1 X132.202 Y124.569 E.05879
G1 X132.202 Y125.372 E.10128
G1 X132.346 Y123.723 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 0.739248
G1 F2406
G1 X132.101 Y122.982 E.08308
; LINE_WIDTH: 0.689696
G1 X131.292 Y122.231 E.10861
; LINE_WIDTH: 0.676734
G1 X131.19 Y122.142 E.01303
G2 X130.758 Y121.819 I-19.711 J25.893 E.052
; LINE_WIDTH: 0.699995
G1 X130.332 Y121.542 E.05091
; LINE_WIDTH: 0.725001
G1 X130.302 Y121.523 E.0036
; LINE_WIDTH: 0.742906
G1 X130.166 Y121.445 E.01686
; LINE_WIDTH: 0.767827
G2 X129.809 Y121.296 I-.723 J1.229 E.04313
; LINE_WIDTH: 0.725451
G1 X129.563 Y121.23 E.02653
; LINE_WIDTH: 0.68153
G2 X128.219 Y120.994 I-1.723 J5.862 E.1327
; LINE_WIDTH: 0.694324
G1 X127.965 Y120.983 E.02523
; LINE_WIDTH: 0.722813
G2 X127.676 Y120.971 I-.369 J5.345 E.03007
; LINE_WIDTH: 0.762783
G2 X127.172 Y121.032 I-.107 J1.219 E.05647
; LINE_WIDTH: 0.730236
G1 X127.138 Y121.041 E.00366
; LINE_WIDTH: 0.702642
G1 X126.648 Y121.177 E.05114
; LINE_WIDTH: 0.67836
G2 X125.617 Y121.59 I1.788 J5.961 E.1074
; LINE_WIDTH: 0.701164
G1 X125.392 Y121.709 E.02552
; LINE_WIDTH: 0.733972
G2 X125.135 Y121.845 I2.397 J4.808 E.03068
; LINE_WIDTH: 0.75978
G1 X125.002 Y121.925 E.0171
G1 X124.742 Y122.167 E.03899
; LINE_WIDTH: 0.685084
G2 X123.687 Y123.438 I4.978 J5.202 E.16163
; LINE_WIDTH: 0.709241
G1 X123.554 Y123.655 E.02587
; LINE_WIDTH: 0.746383
G2 X123.401 Y123.903 I4.517 J2.939 E.03137
; LINE_WIDTH: 0.777225
G1 X123.365 Y123.97 E.00856
; LINE_WIDTH: 0.767519
G1 X123.303 Y124.178 E.02413
; LINE_WIDTH: 0.726832
G2 X123.232 Y124.419 I4.432 J1.437 E.0262
; LINE_WIDTH: 0.683599
G2 X122.98 Y126.017 I6.649 J1.866 E.15794
; LINE_WIDTH: 0.718581
G1 X122.975 Y126.271 E.02627
; LINE_WIDTH: 0.760061
G2 X122.97 Y126.563 I2.179 J.18 E.03214
; LINE_WIDTH: 0.762223
G1 X123.031 Y126.811 E.0281
; LINE_WIDTH: 0.719223
G2 X123.101 Y127.09 I5.223 J-1.154 E.02973
; LINE_WIDTH: 0.683665
G2 X123.698 Y128.594 I6.769 J-1.816 E.15799
; LINE_WIDTH: 0.72725
G1 X123.811 Y128.797 E.02426
; LINE_WIDTH: 0.768446
G2 X123.979 Y129.061 I.714 J-.269 E.03514
; LINE_WIDTH: 0.748285
G1 X124.157 Y129.244 E.0275
; LINE_WIDTH: 0.709579
G2 X124.359 Y129.449 I3.91 J-3.634 E.02922
; LINE_WIDTH: 0.684572
G2 X125.638 Y130.44 I4.923 J-5.035 E.15829
; LINE_WIDTH: 0.735289
G1 X125.804 Y130.537 E.02036
; LINE_WIDTH: 0.769817
G2 X126.124 Y130.684 I.596 J-.873 E.03947
; LINE_WIDTH: 0.73559
G1 X126.37 Y130.752 E.02696
; LINE_WIDTH: 0.683019
G2 X127.711 Y131.001 I1.805 J-5.98 E.13305
; LINE_WIDTH: 0.700836
G1 X128.219 Y131.027 E.05098
; LINE_WIDTH: 0.726353
G1 X128.254 Y131.028 E.00361
; LINE_WIDTH: 0.743976
G1 X128.407 Y131.028 E.01638
; LINE_WIDTH: 0.769964
G2 X128.76 Y130.985 I.075 J-.855 E.04001
; LINE_WIDTH: 0.74133
G1 X128.795 Y130.976 E.00379
; LINE_WIDTH: 0.724158
G1 X129.04 Y130.91 E.02647
; LINE_WIDTH: 0.681374
G2 X130.321 Y130.441 I-1.451 J-5.948 E.13266
; LINE_WIDTH: 0.695063
G1 X130.547 Y130.324 E.02526
; LINE_WIDTH: 0.724058
G2 X130.804 Y130.189 I-2.36 J-4.816 E.03014
; LINE_WIDTH: 0.762623
G2 X131.208 Y129.882 I-.522 J-1.107 E.05646
; LINE_WIDTH: 0.728818
G1 X131.233 Y129.857 E.00364
; LINE_WIDTH: 0.707461
G1 X131.506 Y129.579 E.03948
; LINE_WIDTH: 0.669968
G1 X131.778 Y129.3 E.03709
; LINE_WIDTH: 0.626515
G2 X132.051 Y128.994 I-2.038 J-2.091 E.0362
; LINE_WIDTH: 0.638438
G1 X132.1 Y128.884 E.01082
; LINE_WIDTH: 0.662959
G1 X132.219 Y128.512 E.03673
G1 X134.052 Y128.748 F30000
; LINE_WIDTH: 0.821132
G1 F2406
G1 X135.973 Y129.56 E.25004
G1 X135.977 Y129.554 F30000
; LINE_WIDTH: 0.968504
G1 F2039.284
G1 X134.853 Y129.079 E.17547
; LINE_WIDTH: 0.998192
G1 F1972.924
G1 X134.723 Y129.02 E.02117
; LINE_WIDTH: 1.04705
G1 F1872.632
G1 X134.593 Y128.962 E.02231
; LINE_WIDTH: 1.07649
G1 F1816.992
G3 X134.062 Y128.723 I4.599 J-10.937 E.09399
G1 X131.889 Y131.39 F30000
; LINE_WIDTH: 1.07649
G1 F1816.996
G2 X132.229 Y131.862 I9.788 J-6.697 E.09398
; LINE_WIDTH: 1.04706
G1 F1872.631
G1 X132.312 Y131.977 E.02231
; LINE_WIDTH: 0.998192
G1 F1972.925
G1 X132.395 Y132.093 E.02117
; LINE_WIDTH: 0.968505
G1 F2039.281
G1 X133.131 Y133.066 E.17547
G1 X133.125 Y133.07 F30000
; LINE_WIDTH: 0.821127
G1 F2406
G1 X131.867 Y131.405 E.25004
G1 X128.673 Y132.612 F30000
; LINE_WIDTH: 1.08387
G1 F1803.563
G2 X128.732 Y133.191 I11.83 J-.907 E.09468
; LINE_WIDTH: 1.04705
G1 F1872.649
G1 X128.746 Y133.333 E.02231
; LINE_WIDTH: 0.998184
G1 F1972.942
G1 X128.76 Y133.474 E.02117
; LINE_WIDTH: 0.973751
G1 F2027.231
G1 X128.911 Y134.685 E.17651
G1 X128.903 Y134.685 F30000
; LINE_WIDTH: 0.839449
G1 F2388.508
G1 X128.646 Y132.615 E.25626
G1 X125.277 Y132.062 F30000
; LINE_WIDTH: 1.08387
G1 F1803.552
G2 X125.038 Y132.593 I10.717 J5.138 E.09469
; LINE_WIDTH: 1.04705
G1 F1872.649
G1 X124.98 Y132.723 E.02231
; LINE_WIDTH: 0.998182
G1 F1972.945
G1 X124.921 Y132.853 E.02117
; LINE_WIDTH: 0.973752
G1 F2027.229
G1 X124.446 Y133.977 E.17651
G1 X124.44 Y133.973 F30000
; LINE_WIDTH: 0.839442
G1 F2388.53
G1 X125.252 Y132.052 E.25627
; CHANGE_LAYER
; Z_HEIGHT: 9.6
; LAYER_HEIGHT: 0.400001
; WIPE_START
G1 F24000
G1 X124.473 Y133.894 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 24/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L24
M991 S0 P23 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z9.6 I1.024 J.657 P1  F30000
G1 X131.343 Y123.182 Z9.6
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2451.784
G1 X131.444 Y123.276 E.01648
G1 X131.444 Y128.724 E.65185
G1 X130.78 Y129.34 E.10839
G3 X127.839 Y121.662 I-2.777 J-3.339 E1.9731
G3 X130.78 Y122.66 I.147 J4.4 E.37981
G1 X131.255 Y123.101 E.07755
G1 X130.71 Y123.596 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X127.844 Y122.396 I-2.307 J-2.775 E1.63669
G1 X128.17 Y122.393 E.03897
G3 X130.627 Y123.509 I-.217 J3.743 E.33037
M204 S10000
; WIPE_START
G1 F24000
G1 X130.661 Y125.509 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X124.435 Y129.924 Z10 F30000
G1 X124.123 Y130.146 Z10
G1 Z9.6
G1 E3 F1800
; FEATURE: Inner wall
G1 F2451.784
G1 X123.581 Y129.697 E.08415
G1 X123.058 Y130.037 E.07475
G1 X122.81 Y129.712 E.04895
G1 X123.278 Y129.297 E.07482
G3 X122.325 Y126.992 I15.82 J-7.889 E.29874
G1 X121.701 Y127.025 E.07475
G1 X121.649 Y126.619 E.04895
G1 X122.262 Y126.495 E.07481
G3 X122.589 Y124.021 I17.644 J1.078 E.29874
G1 X122.032 Y123.738 E.07475
G1 X122.19 Y123.361 E.04895
G1 X122.783 Y123.559 E.07481
G3 X124.303 Y121.581 I14.741 J9.755 E.29874
G1 X123.963 Y121.058 E.07475
G1 X124.288 Y120.81 E.04895
G1 X124.703 Y121.278 E.07482
G3 X127.008 Y120.325 I7.889 J15.82 E.29874
G1 X126.975 Y119.701 E.07475
G1 X127.381 Y119.649 E.04895
G1 X127.505 Y120.262 E.07481
G3 X129.979 Y120.589 I-1.078 J17.644 E.29874
G1 X130.262 Y120.032 E.07475
G1 X130.639 Y120.19 E.04895
G1 X130.441 Y120.783 E.07481
G3 X132.419 Y122.303 I-9.756 J14.742 E.29874
G1 X132.942 Y121.963 E.07476
G1 X133.19 Y122.288 E.04895
G1 X132.722 Y122.703 E.07482
G3 X133.675 Y125.008 I-15.821 J7.89 E.29874
G1 X134.299 Y124.975 E.07475
G1 X134.351 Y125.381 E.04895
G1 X133.738 Y125.505 E.07481
G3 X133.411 Y127.979 I-17.644 J-1.078 E.29874
G1 X133.968 Y128.262 E.07475
G1 X133.81 Y128.639 E.04895
G1 X133.217 Y128.441 E.07482
G3 X131.697 Y130.419 I-14.743 J-9.757 E.29874
G1 X132.037 Y130.942 E.07476
G1 X131.712 Y131.19 E.04895
G1 X131.297 Y130.722 E.07482
G3 X128.992 Y131.675 I-7.889 J-15.821 E.29874
G1 X129.025 Y132.299 E.07475
G1 X128.619 Y132.351 E.04895
G1 X128.495 Y131.738 E.07481
G3 X126.021 Y131.411 I1.078 J-17.644 E.29874
G1 X125.738 Y131.968 E.07475
G1 X125.361 Y131.81 E.04895
G1 X125.559 Y131.217 E.07481
G3 X124.504 Y130.461 I9.756 J-14.742 E.15537
G1 X124.215 Y130.222 E.04484
G1 X123.47 Y130.645 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G3 X120.99 Y131.801 I-4.422 J-6.248 E.32912
G1 X120.885 Y131.675 E.01959
G1 X120.882 Y131.672 E.00054
G3 X120.564 Y131.244 I4.737 J-3.858 E.06378
G3 X122.383 Y129.109 I6.642 J3.816 E.33758
G3 X121.824 Y127.754 I10.073 J-4.948 E.17551
G1 X121.754 Y127.758 E.00841
G3 X119.029 Y127.519 I-.705 J-7.622 E.32912
G1 X119 Y127.357 E.01959
G1 X119 Y127.353 E.00054
G3 X118.938 Y126.824 I6.032 J-.973 E.06378
G3 X121.581 Y125.884 I3.844 J6.626 E.33758
G3 X121.775 Y124.431 I11.196 J.751 E.17551
G1 X121.712 Y124.399 E.00841
G3 X119.471 Y122.83 I3.2 J-6.954 E.32912
G1 X119.527 Y122.676 E.01959
G1 X119.529 Y122.672 E.00054
G3 X119.74 Y122.182 I5.71 J2.173 E.06378
G3 X122.499 Y122.69 I.016 J7.66 E.33758
G3 X123.393 Y121.529 I9.321 J6.249 E.17551
G1 X123.355 Y121.47 E.00841
G3 X122.199 Y118.99 I6.248 J-4.422 E.32912
G1 X122.325 Y118.885 E.01959
G1 X122.328 Y118.882 E.00054
G3 X122.756 Y118.564 I3.858 J4.737 E.06378
G3 X124.891 Y120.383 I-3.816 J6.642 E.33758
G3 X126.246 Y119.824 I4.948 J10.073 E.17551
G1 X126.242 Y119.754 E.00841
G3 X126.481 Y117.029 I7.622 J-.705 E.32912
G1 X126.643 Y117 E.01959
G1 X126.647 Y117 E.00054
G3 X127.177 Y116.938 I.973 J6.035 E.06381
G3 X128.116 Y119.581 I-6.634 J3.846 E.33757
G3 X129.569 Y119.775 I-.751 J11.196 E.17551
G1 X129.601 Y119.712 E.00841
G3 X131.17 Y117.471 I6.954 J3.2 E.32912
G1 X131.324 Y117.527 E.01959
M73 P94 R0
G1 X131.328 Y117.529 E.00054
G3 X131.818 Y117.74 I-2.173 J5.71 E.06378
G3 X131.31 Y120.499 I-7.66 J.016 E.33758
G3 X132.471 Y121.393 I-6.249 J9.321 E.17551
G1 X132.53 Y121.355 E.00841
G3 X135.01 Y120.199 I4.422 J6.248 E.32912
G1 X135.115 Y120.325 E.01959
G1 X135.118 Y120.328 E.00054
G3 X135.436 Y120.756 I-4.737 J3.858 E.06378
G3 X133.617 Y122.891 I-6.642 J-3.816 E.33758
G3 X134.176 Y124.246 I-10.073 J4.948 E.17551
G1 X134.246 Y124.242 E.00841
G3 X136.971 Y124.481 I.705 J7.622 E.32912
G1 X137 Y124.643 E.01959
G1 X137 Y124.647 E.00054
G3 X137.062 Y125.176 I-6.032 J.973 E.06378
G3 X134.419 Y126.116 I-3.844 J-6.626 E.33758
G3 X134.225 Y127.569 I-11.196 J-.751 E.17551
G1 X134.288 Y127.601 E.00841
G3 X136.529 Y129.17 I-3.2 J6.954 E.32912
G1 X136.473 Y129.324 E.01959
G1 X136.471 Y129.328 E.00054
G3 X136.26 Y129.818 I-5.711 J-2.174 E.06378
G3 X133.501 Y129.31 I-.016 J-7.66 E.33758
G3 X132.607 Y130.471 I-9.322 J-6.249 E.17551
G1 X132.645 Y130.53 E.00841
G3 X133.801 Y133.01 I-6.248 J4.422 E.32912
G1 X133.675 Y133.115 E.01959
G1 X133.672 Y133.118 E.00054
G3 X133.244 Y133.436 I-3.858 J-4.737 E.06378
G3 X131.109 Y131.617 I3.816 J-6.642 E.33758
G3 X129.754 Y132.176 I-4.948 J-10.073 E.17551
G1 X129.758 Y132.246 E.00841
G3 X129.519 Y134.971 I-7.622 J.705 E.32912
G1 X129.357 Y135 E.01959
G1 X129.353 Y135 E.00054
G3 X128.824 Y135.062 I-.973 J-6.031 E.06378
G3 X127.884 Y132.419 I6.626 J-3.844 E.33758
G3 X126.431 Y132.225 I.751 J-11.196 E.17551
G1 X126.399 Y132.288 E.00841
G3 X124.83 Y134.529 I-6.953 J-3.2 E.32912
G1 X124.676 Y134.473 E.01959
G1 X124.672 Y134.471 E.00054
G3 X124.182 Y134.26 I2.173 J-5.71 E.06378
G3 X124.69 Y131.501 I7.66 J-.016 E.33758
G3 X123.566 Y130.64 I6.249 J-9.321 E.16956
M204 S10000
; WIPE_START
G1 F24000
G1 X122.975 Y130.967 E-.96328
G1 X122.363 Y131.304 E-.99463
G1 X121.788 Y131.55 E-.89209
; WIPE_END
G1 E-.15 F1800
G1 X122.642 Y130.098 Z10 F30000
G1 Z9.6
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 1.04488
G1 F1876.887
G1 X122.337 Y130.33 E.05999
; LINE_WIDTH: 0.997485
G1 F1974.455
G1 X122.031 Y130.563 E.05702
; LINE_WIDTH: 0.973791
G1 F2027.142
G1 X121.079 Y131.325 E.17651
G1 X121.075 Y131.319 F30000
; LINE_WIDTH: 0.839468
G1 F2388.447
G1 X122.627 Y130.077 E.24411
G1 X122.622 Y130.071 F30000
; LINE_WIDTH: 0.666521
G1 F3000
G1 X121.071 Y131.314 E.1881
G1 X123.977 Y129.084 F30000
; LINE_WIDTH: 0.778023
G1 F2600.473
G1 X124.152 Y129.258 E.02789
; LINE_WIDTH: 0.731351
G1 F2788.489
G2 X124.352 Y129.455 I3.76 J-3.617 E.02956
; LINE_WIDTH: 0.686743
G1 F2995.495
G2 X125.639 Y130.438 I5.284 J-5.581 E.15887
; LINE_WIDTH: 0.73577
G1 F2769.531
G1 X125.848 Y130.56 E.02566
; LINE_WIDTH: 0.781668
G1 F2586.848
G1 X126.058 Y130.682 E.02747
G1 X126.119 Y130.7 E.00724
; LINE_WIDTH: 0.764663
G1 F2651.65
G1 X126.366 Y130.763 E.0282
; LINE_WIDTH: 0.720922
G1 F2834.281
G2 X126.645 Y130.834 I1.446 J-5.154 E.02982
; LINE_WIDTH: 0.686765
G1 F2995.388
G2 X128.219 Y131.025 I1.69 J-7.315 E.15558
; LINE_WIDTH: 0.722556
G1 F2827.011
G1 X128.254 Y131.026 E.00357
; LINE_WIDTH: 0.744544
G1 F2732.64
G1 X128.456 Y131.025 E.02174
; LINE_WIDTH: 0.784434
G1 F2576.608
G2 X128.798 Y130.991 I.082 J-.911 E.03932
; LINE_WIDTH: 0.750509
G1 F2708.117
G1 X129.043 Y130.92 E.02759
; LINE_WIDTH: 0.711061
G1 F2878.987
G2 X129.318 Y130.84 I-1.362 J-5.162 E.0293
; LINE_WIDTH: 0.680053
G1 F3000
G2 X130.321 Y130.44 I-2.104 J-6.735 E.10459
; LINE_WIDTH: 0.692802
G1 F2965.591
G1 X130.546 Y130.322 E.02516
; LINE_WIDTH: 0.720505
G1 F2836.147
G2 X130.802 Y130.187 I-2.371 J-4.81 E.02994
; LINE_WIDTH: 0.753971
G1 F2694.086
G1 X130.942 Y130.104 E.01772
; LINE_WIDTH: 0.785294
G1 F2573.439
G2 X131.217 Y129.893 I-.326 J-.709 E.0398
; LINE_WIDTH: 0.757528
G1 F2679.819
G1 X131.243 Y129.868 E.00398
; LINE_WIDTH: 0.731343
G1 F2788.528
G1 X131.484 Y129.613 E.0369
; LINE_WIDTH: 0.685663
G1 F3000
G1 X131.725 Y129.358 E.03429
; LINE_WIDTH: 0.639983
G1 X131.966 Y129.103 E.03168
; LINE_WIDTH: 0.614238
G2 X132.06 Y128.979 I-.491 J-.469 E.01343
; LINE_WIDTH: 0.640017
G1 X132.1 Y128.884 E.0093
; LINE_WIDTH: 0.675211
G1 X132.16 Y128.694 E.01915
; LINE_WIDTH: 0.688057
G1 F2988.957
G1 X132.22 Y128.504 E.01956
G1 X132.172 Y126.653 F30000
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.788937
G1 F2560.103
G1 X132.154 Y127.084 E.04941
; LINE_WIDTH: 0.740408
G1 F2749.908
G2 X132.135 Y127.752 I7.885 J.549 E.0713
G1 X132.717 Y127.937 E.06506
; LINE_WIDTH: 0.752485
G1 F2700.091
G1 X132.802 Y127.325 E.06709
; LINE_WIDTH: 0.789668
G1 F2557.446
G1 X132.892 Y126.688 E.07379
; LINE_WIDTH: 0.822442
G1 F2443.656
G1 X132.937 Y126.062 E.07536
; LINE_WIDTH: 0.865035
G1 F2310.078
G1 X132.983 Y125.436 E.07971
G1 X132.961 Y125.262 E.02227
G1 X132.652 Y124.429 E.11286
G1 X132.202 Y124.619 E.06197
G1 X132.202 Y125.398 E.09892
; LINE_WIDTH: 0.852998
G1 F2346.323
G1 X132.189 Y125.965 E.07098
; LINE_WIDTH: 0.83772
G1 F2394.001
G1 X132.175 Y126.533 E.06957
G1 X134.47 Y128.105 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 1.06083
G1 F1846.168
G1 X134.681 Y128.781 E.11253
G1 X134.808 Y128.834 E.02195
; LINE_WIDTH: 0.997475
G1 F1974.477
G1 X134.936 Y128.888 E.02052
; LINE_WIDTH: 0.968528
G1 F2039.228
G1 X136.072 Y129.331 E.17546
G1 X136.069 Y129.338 F30000
; LINE_WIDTH: 0.821155
G1 F2447.933
G1 X134.218 Y128.615 E.23818
G1 X134.215 Y128.622 F30000
; LINE_WIDTH: 0.650022
G1 F3000
G1 X136.067 Y129.344 E.18275
; WIPE_START
G1 F24000
G1 X134.215 Y128.622 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X132.55 Y131.058 Z10 F30000
G1 Z9.6
G1 E3 F1800
; LINE_WIDTH: 1.06083
G1 F1846.172
G1 X132.395 Y131.749 E.11254
G1 X132.479 Y131.859 E.02195
; LINE_WIDTH: 0.997479
G1 F1974.467
G1 X132.563 Y131.969 E.02052
; LINE_WIDTH: 0.968527
G1 F2039.229
G1 X133.325 Y132.921 E.17546
G1 X133.319 Y132.925 F30000
; LINE_WIDTH: 0.821156
G1 F2447.929
G1 X132.077 Y131.373 E.23818
G1 X132.071 Y131.378 F30000
; LINE_WIDTH: 0.650022
G1 F3000
G1 X133.314 Y132.929 E.18275
; WIPE_START
G1 F24000
G1 X132.071 Y131.378 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X129.412 Y132.655 Z10 F30000
G1 Z9.6
G1 E3 F1800
; LINE_WIDTH: 1.06131
G1 F1845.264
G1 X128.932 Y133.176 E.11259
; LINE_WIDTH: 1.04488
G1 F1876.872
G1 X128.95 Y133.313 E.02159
; LINE_WIDTH: 0.99749
G1 F1974.444
G1 X128.967 Y133.45 E.02052
; LINE_WIDTH: 0.973793
G1 F2027.135
G1 X129.152 Y134.656 E.17651
G1 X129.144 Y134.657 F30000
; LINE_WIDTH: 0.83947
G1 F2388.442
G1 X128.844 Y132.692 E.24412
G1 X128.837 Y132.693 F30000
; LINE_WIDTH: 0.666501
G1 F3000
G1 X129.137 Y134.658 E.18809
; WIPE_START
G1 F24000
G1 X128.837 Y132.693 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X125.112 Y132.936 Z10 F30000
G1 Z9.6
G1 E3 F1800
; LINE_WIDTH: 0.997474
G1 F1974.478
G1 X125.261 Y132.582 E.05703
; LINE_WIDTH: 1.04487
G1 F1876.89
G1 X125.409 Y132.228 E.05999
G1 X125.385 Y132.218 F30000
; LINE_WIDTH: 0.839481
G1 F2388.408
G1 X124.662 Y134.069 E.24412
G1 X124.656 Y134.067 F30000
; LINE_WIDTH: 0.666535
G1 F3000
G1 X125.378 Y132.215 E.1881
G1 X125.112 Y132.936 F30000
; LINE_WIDTH: 0.973775
G1 F2027.178
G1 X124.669 Y134.072 E.1765
; WIPE_START
G1 F24000
G1 X125.112 Y132.936 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.977 Y129.084 Z10 F30000
G1 Z9.6
G1 E3 F1800
; LINE_WIDTH: 0.79781
G1 F2528.199
G1 X123.968 Y129.071 E.00182
; LINE_WIDTH: 0.770007
G1 F2630.939
G3 X123.824 Y128.816 I4.639 J-2.797 E.03269
; LINE_WIDTH: 0.725439
G1 F2814.267
G1 X123.699 Y128.593 E.02657
; LINE_WIDTH: 0.686916
G1 F2994.634
G3 X123.091 Y127.093 I6.594 J-3.545 E.15889
; LINE_WIDTH: 0.739827
G1 F2752.35
G3 X123.028 Y126.86 I4.306 J-1.28 E.02578
; LINE_WIDTH: 0.782997
G1 F2581.917
G1 X122.975 Y126.659 E.02358
; LINE_WIDTH: 0.790844
G1 F2553.179
G1 X122.972 Y126.563 E.011
; LINE_WIDTH: 0.755413
G1 F2688.285
G3 X122.977 Y126.271 I5.402 J-.06 E.03187
; LINE_WIDTH: 0.715225
G1 F2859.939
G1 X122.982 Y126.016 E.02613
; LINE_WIDTH: 0.682702
G1 F3000
G3 X123.166 Y124.664 I6.703 J.223 E.13301
; LINE_WIDTH: 0.716716
G1 F2853.181
G1 X123.221 Y124.416 E.02615
; LINE_WIDTH: 0.732239
G1 F2784.661
G1 X123.229 Y124.382 E.00368
; LINE_WIDTH: 0.774712
G1 F2612.972
G1 X123.32 Y124.059 E.03767
G1 X123.404 Y123.904 E.01972
; LINE_WIDTH: 0.742104
G1 F2742.802
G3 X123.555 Y123.656 I4.668 J2.675 E.03113
; LINE_WIDTH: 0.70627
G1 F2901.219
G1 X123.688 Y123.439 E.02574
; LINE_WIDTH: 0.683205
G1 F3000
G3 X124.535 Y122.368 I5.576 J3.537 E.13312
; LINE_WIDTH: 0.727266
G1 F2806.249
G1 X124.708 Y122.182 E.0266
; LINE_WIDTH: 0.745121
G1 F2730.252
G1 X124.733 Y122.156 E.00383
; LINE_WIDTH: 0.781614
G1 F2587.048
G3 X125.027 Y121.913 I.682 J.524 E.04362
; LINE_WIDTH: 0.76281
G1 F2658.91
G1 X125.137 Y121.847 E.01409
; LINE_WIDTH: 0.730067
G1 F2794.052
G3 X125.392 Y121.71 I2.663 J4.664 E.03047
; LINE_WIDTH: 0.698564
G1 F2937.706
G1 X125.617 Y121.591 E.02541
; LINE_WIDTH: 0.684595
G1 F3000
G3 X126.891 Y121.099 I2.961 J5.778 E.13346
; LINE_WIDTH: 0.73907
G1 F2755.541
G1 X127.135 Y121.027 E.02711
; LINE_WIDTH: 0.783062
G1 F2581.679
G3 X127.509 Y120.974 I.355 J1.174 E.04309
; LINE_WIDTH: 0.752813
G1 F2698.762
G1 X127.676 Y120.973 E.01821
; LINE_WIDTH: 0.719287
G1 F2841.601
G3 X127.965 Y120.984 I-.067 J5.351 E.02987
; LINE_WIDTH: 0.692096
G1 F2969.045
G1 X128.22 Y120.995 E.02513
; LINE_WIDTH: 0.680159
G1 F3000
G3 X129.287 Y121.152 I-.497 J7.107 E.10461
; LINE_WIDTH: 0.712164
G1 F2873.917
G3 X129.566 Y121.22 I-1.127 J5.22 E.02936
; LINE_WIDTH: 0.752122
G1 F2701.562
G1 X129.814 Y121.281 E.02766
; LINE_WIDTH: 0.784377
G1 F2576.817
G3 X130.122 Y121.422 I-.206 J.856 E.0388
; LINE_WIDTH: 0.743471
G1 F2737.101
G1 X130.301 Y121.525 E.02221
; LINE_WIDTH: 0.721256
G1 F2832.792
G1 X130.331 Y121.543 E.00356
; LINE_WIDTH: 0.686963
G1 F2994.4
G3 X131.623 Y122.521 I-3.925 J6.531 E.15904
; LINE_WIDTH: 0.717383
G1 F2850.167
G1 X132.031 Y122.879 E.0559
; LINE_WIDTH: 0.741857
G1 F2743.834
G1 X132.396 Y123.713 E.09738
G1 X133.378 Y121.929 F30000
; LINE_WIDTH: 0.650021
G1 F3000
G1 X134.929 Y120.686 E.18275
G1 X134.925 Y120.681 F30000
; LINE_WIDTH: 0.821156
G1 F2447.929
G1 X133.373 Y121.923 E.23818
G1 X133.058 Y121.449 F30000
; LINE_WIDTH: 1.06083
G1 F1846.175
G1 X133.749 Y121.605 E.11253
G1 X133.859 Y121.521 E.02195
; LINE_WIDTH: 0.997479
G1 F1974.468
G1 X133.969 Y121.437 E.02052
; LINE_WIDTH: 0.968526
G1 F2039.232
G1 X134.921 Y120.675 E.17546
; WIPE_START
G1 F24000
G1 X133.969 Y121.437 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X131.106 Y119.951 Z10 F30000
G1 Z9.6
G1 E3 F1800
; LINE_WIDTH: 1.06086
G1 F1846.109
G1 X130.781 Y119.319 E.11291
G1 X130.834 Y119.192 E.02195
; LINE_WIDTH: 0.99748
G1 F1974.466
G1 X130.888 Y119.064 E.02052
; LINE_WIDTH: 0.968531
G1 F2039.219
G1 X131.331 Y117.928 E.17546
G1 X131.338 Y117.931 F30000
; LINE_WIDTH: 0.821157
G1 F2447.925
G1 X130.615 Y119.782 E.23819
G1 X130.622 Y119.785 F30000
; LINE_WIDTH: 0.650012
G1 F3000
G1 X131.344 Y117.933 E.18275
; WIPE_START
G1 F24000
G1 X130.622 Y119.785 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X127.033 Y118.55 Z10 F30000
G1 Z9.6
G1 E3 F1800
; LINE_WIDTH: 0.997477
G1 F1974.473
G1 X127.082 Y118.93 E.05703
; LINE_WIDTH: 1.04488
G1 F1876.884
G1 X127.13 Y119.311 E.05999
G1 X127.155 Y119.308 F30000
; LINE_WIDTH: 0.839475
G1 F2388.426
G1 X126.856 Y117.343 E.24412
G1 X126.863 Y117.342 F30000
; LINE_WIDTH: 0.6665
G1 F3000
G1 X127.163 Y119.307 E.18809
G1 X127.033 Y118.55 F30000
; LINE_WIDTH: 0.973775
G1 F2027.176
G1 X126.848 Y117.344 E.1765
; WIPE_START
G1 F24000
G1 X127.033 Y118.55 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X123.437 Y120.031 Z10 F30000
G1 Z9.6
G1 E3 F1800
; LINE_WIDTH: 0.997486
G1 F1974.452
G1 X123.67 Y120.337 E.05702
; LINE_WIDTH: 1.04488
G1 F1876.885
G1 X123.902 Y120.642 E.05999
G1 X123.923 Y120.627 F30000
; LINE_WIDTH: 0.839468
G1 F2388.45
G1 X122.681 Y119.075 E.24411
G1 X122.686 Y119.071 F30000
; LINE_WIDTH: 0.66653
G1 F3000
G1 X123.929 Y120.622 E.1881
G1 X123.437 Y120.031 F30000
; LINE_WIDTH: 0.97379
G1 F2027.144
G1 X122.675 Y119.079 E.17651
; WIPE_START
G1 F24000
G1 X123.437 Y120.031 E-2.85
; WIPE_END
G1 E-.15 F1800
M73 P95 R0
G1 X121.064 Y123.112 Z10 F30000
G1 Z9.6
G1 E3 F1800
; LINE_WIDTH: 0.997476
G1 F1974.475
G1 X121.418 Y123.261 E.05703
; LINE_WIDTH: 1.04488
G1 F1876.882
G1 X121.772 Y123.409 E.05999
G1 X121.782 Y123.385 F30000
; LINE_WIDTH: 0.839482
G1 F2388.404
G1 X119.931 Y122.662 E.24412
G1 X119.933 Y122.656 F30000
; LINE_WIDTH: 0.666526
G1 F3000
G1 X121.785 Y123.378 E.1881
G1 X121.064 Y123.112 F30000
; LINE_WIDTH: 0.973775
G1 F2027.176
G1 X119.928 Y122.669 E.1765
; WIPE_START
G1 F24000
G1 X121.064 Y123.112 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X120.55 Y126.967 Z10 F30000
G1 Z9.6
G1 E3 F1800
; LINE_WIDTH: 0.997483
G1 F1974.459
G1 X120.93 Y126.918 E.05703
; LINE_WIDTH: 1.04488
G1 F1876.88
G1 X121.311 Y126.87 E.05999
G1 X121.308 Y126.844 F30000
; LINE_WIDTH: 0.83948
G1 F2388.411
G1 X119.343 Y127.144 E.24412
G1 X119.342 Y127.137 F30000
; LINE_WIDTH: 0.666496
G1 F3000
G1 X121.307 Y126.837 E.18809
G1 X120.55 Y126.967 F30000
; LINE_WIDTH: 0.973783
G1 F2027.159
G1 X119.344 Y127.152 E.17651
; WIPE_START
G1 F24000
G1 X120.55 Y126.967 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X128.121 Y126.001 Z10 F30000
G1 X134.693 Y125.163 Z10
G1 Z9.6
G1 E3 F1800
; LINE_WIDTH: 0.650013
G1 F3000
G1 X136.658 Y124.863 E.18275
G1 X136.657 Y124.856 F30000
; LINE_WIDTH: 0.821153
G1 F2447.939
G1 X134.692 Y125.156 E.23819
G1 X134.655 Y124.588 F30000
; LINE_WIDTH: 1.06084
G1 F1846.152
G1 X135.176 Y125.068 E.11253
G1 X135.313 Y125.05 E.02195
; LINE_WIDTH: 0.997486
G1 F1974.453
G1 X135.45 Y125.033 E.02052
; LINE_WIDTH: 0.96853
G1 F2039.223
G1 X136.656 Y124.848 E.17547
; CHANGE_LAYER
; Z_HEIGHT: 10
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X135.45 Y125.033 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
; layer num/total_layer_count: 25/25
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L25
M991 S0 P24 ;notify layer change
; start printing object, unique label id: 72
M624 AQAAAAAAAAA=
G17
G3 Z10 I.353 J-1.165 P1  F30000
G1 X130.71 Y123.596 Z10
G1 E3 F1800
M204 S5000
; FEATURE: Outer wall
; LINE_WIDTH: 0.82
G1 F2451.784
G1 X130.71 Y128.404 E.57521
G1 X130.31 Y128.775 E.06532
G3 X127.795 Y122.396 I-2.306 J-2.776 E1.63099
G1 X128.17 Y122.393 E.04482
G3 X130.627 Y123.509 I-.217 J3.743 E.33037
M204 S10000
; WIPE_START
G1 F24000
G1 X130.661 Y125.509 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X124.539 Y130.066 Z10.4 F30000
G1 X123.596 Y130.768 Z10.4
G1 Z10
G1 E3 F1800
M204 S5000
G1 F2451.784
G3 X121.152 Y131.994 I-4.533 J-5.985 E.32902
G3 X121.047 Y131.871 I1.368 J-1.261 E.01941
G3 X120.711 Y131.447 I4.68 J-4.067 E.06473
G3 X122.483 Y129.266 I6.3 J3.308 E.33847
G3 X121.878 Y127.92 I8.287 J-4.531 E.17672
G1 X121.802 Y127.927 E.00917
G3 X119.072 Y127.767 I-.933 J-7.449 E.32902
G3 X119.044 Y127.608 I1.817 J-.408 E.01941
G3 X118.964 Y127.073 I6.085 J-1.182 E.06473
G3 X121.589 Y126.07 I3.898 J6.268 E.33831
G3 X121.738 Y124.602 I9.442 J.22 E.17672
G1 X121.669 Y124.57 E.00917
G3 X119.385 Y123.067 I2.917 J-6.918 E.32902
G3 X119.44 Y122.914 I1.779 J.555 E.01941
G3 X119.638 Y122.411 I5.862 J2.019 E.06473
G3 X122.413 Y122.855 I.285 J7.11 E.33847
G3 X123.276 Y121.659 I8.067 J4.911 E.17672
G1 X123.232 Y121.596 E.00917
G3 X122.006 Y119.152 I5.985 J-4.533 E.32902
G3 X122.129 Y119.047 I1.262 J1.37 E.01941
G3 X122.553 Y118.711 I4.067 J4.68 E.06473
G3 X124.734 Y120.483 I-3.308 J6.3 E.33847
G3 X126.08 Y119.878 I4.531 J8.287 E.17672
G1 X126.073 Y119.802 E.00917
G3 X126.233 Y117.072 I7.449 J-.933 E.32902
G3 X126.392 Y117.044 I.408 J1.815 E.01941
G3 X126.927 Y116.964 I1.182 J6.084 E.06472
G3 X127.93 Y119.589 I-6.011 J3.801 E.33847
G3 X129.398 Y119.738 I-.22 J9.442 E.17672
G1 X129.43 Y119.669 E.00917
G3 X130.933 Y117.385 I6.918 J2.917 E.32902
G3 X131.086 Y117.44 I-.555 J1.777 E.01941
G3 X131.589 Y117.638 I-2.02 J5.863 E.06473
G3 X131.145 Y120.413 I-7.11 J.285 E.33847
G3 X132.341 Y121.276 I-4.911 J8.068 E.17672
G1 X132.404 Y121.232 E.00917
G3 X134.848 Y120.006 I4.533 J5.985 E.32902
G3 X134.953 Y120.129 I-1.37 J1.262 E.01941
G3 X135.289 Y120.553 I-4.68 J4.067 E.06473
G3 X133.517 Y122.734 I-6.3 J-3.308 E.33847
G3 X134.122 Y124.08 I-8.287 J4.531 E.17672
G1 X134.198 Y124.073 E.00917
G3 X136.928 Y124.233 I.933 J7.449 E.32902
G3 X136.956 Y124.392 I-1.817 J.408 E.01941
G3 X137.036 Y124.927 I-6.085 J1.182 E.06473
G3 X134.411 Y125.93 I-3.898 J-6.268 E.33831
G3 X134.262 Y127.398 I-9.442 J-.22 E.17672
G1 X134.331 Y127.43 E.00917
G3 X136.615 Y128.933 I-2.917 J6.918 E.32902
G3 X136.56 Y129.086 I-1.778 J-.555 E.01941
G3 X136.362 Y129.589 I-5.862 J-2.019 E.06473
G3 X133.587 Y129.145 I-.285 J-7.11 E.33847
G3 X132.724 Y130.341 I-8.068 J-4.911 E.17672
G1 X132.768 Y130.404 E.00917
G3 X133.994 Y132.848 I-5.985 J4.533 E.32902
G3 X133.871 Y132.953 I-1.261 J-1.368 E.01941
G3 X133.447 Y133.289 I-4.067 J-4.68 E.06473
G3 X131.266 Y131.517 I3.308 J-6.3 E.33847
G3 X129.92 Y132.122 I-4.531 J-8.287 E.17672
G1 X129.927 Y132.198 E.00917
G3 X129.767 Y134.928 I-7.449 J.933 E.32902
G3 X129.608 Y134.956 I-.408 J-1.816 E.01941
G3 X129.073 Y135.036 I-1.182 J-6.086 E.06473
G3 X128.07 Y132.411 I6.268 J-3.898 E.33831
G3 X126.602 Y132.262 I.22 J-9.442 E.17672
G1 X126.57 Y132.331 E.00917
G3 X125.067 Y134.615 I-6.918 J-2.917 E.32902
G3 X124.914 Y134.56 I.554 J-1.777 E.01941
G3 X124.411 Y134.362 I2.02 J-5.863 E.06473
G3 X124.855 Y131.587 I7.11 J-.285 E.33847
G3 X123.692 Y130.752 I4.911 J-8.068 E.17153
M204 S10000
; WIPE_START
G1 F24000
G1 X122.894 Y131.246 E-1.33788
G1 X122.284 Y131.574 E-.98666
G1 X121.944 Y131.716 E-.52546
; WIPE_END
G1 E-.15 F1800
G1 X122.893 Y130.127 Z10.4 F30000
G1 Z10
G1 E3 F1800
; FEATURE: Gap infill
; LINE_WIDTH: 1.10272
G1 F1770.115
G1 X122.442 Y130.501 E.09698
; LINE_WIDTH: 1.07405
G1 F1821.483
G1 X122.336 Y130.584 E.0218
; LINE_WIDTH: 1.03942
G1 F1887.634
G1 X121.779 Y131.045 E.11232
; LINE_WIDTH: 1.02466
G1 F1917.307
G1 X121.222 Y131.506 E.11058
; WIPE_START
G1 F24000
G1 X121.779 Y131.045 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X125.641 Y132.128 Z10.4 F30000
G1 Z10
G1 E3 F1800
; LINE_WIDTH: 1.10272
G1 F1770.129
G1 X125.437 Y132.676 E.09697
; LINE_WIDTH: 1.07405
G1 F1821.482
G1 X125.387 Y132.802 E.0218
; LINE_WIDTH: 1.03942
G1 F1887.624
G1 X125.135 Y133.48 E.11232
; LINE_WIDTH: 1.02466
G1 F1917.294
G1 X124.883 Y134.157 E.11058
; WIPE_START
G1 F24000
G1 X125.135 Y133.48 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X129.379 Y134.623 Z10.4 F30000
G1 Z10
G1 E3 F1800
; LINE_WIDTH: 1.00989
G1 F1947.943
G1 X129.259 Y133.91 E.10884
; LINE_WIDTH: 1.03941
G1 F1887.637
G1 X129.138 Y133.197 E.11232
; LINE_WIDTH: 1.07405
G1 F1821.482
G1 X129.119 Y133.063 E.0218
; LINE_WIDTH: 1.09392
G1 F1785.577
G1 X129.021 Y132.487 E.09615
; WIPE_START
G1 F24000
G1 X129.119 Y133.063 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X132.127 Y131.107 Z10.4 F30000
G1 Z10
G1 E3 F1800
; LINE_WIDTH: 1.09392
G1 F1785.574
G1 X132.501 Y131.558 E.09614
; LINE_WIDTH: 1.07405
G1 F1821.482
G1 X132.584 Y131.664 E.0218
; LINE_WIDTH: 1.03942
G1 F1887.634
G1 X133.045 Y132.221 E.11232
; LINE_WIDTH: 1.0099
G1 F1947.929
G1 X133.506 Y132.778 E.10884
; WIPE_START
G1 F24000
G1 X133.045 Y132.221 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X134.128 Y128.359 Z10.4 F30000
G1 Z10
G1 E3 F1800
; LINE_WIDTH: 1.09391
G1 F1785.587
G1 X134.676 Y128.563 E.09613
; LINE_WIDTH: 1.07405
G1 F1821.485
G1 X134.802 Y128.613 E.0218
; LINE_WIDTH: 1.03942
G1 F1887.627
G1 X135.48 Y128.865 E.11232
; LINE_WIDTH: 1.00991
G1 F1947.913
G1 X136.157 Y129.117 E.10884
; WIPE_START
M73 P96 R0
G1 F24000
G1 X135.48 Y128.865 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X136.623 Y124.621 Z10.4 F30000
G1 Z10
G1 E3 F1800
; LINE_WIDTH: 1.00989
G1 F1947.941
G1 X135.91 Y124.741 E.10884
; LINE_WIDTH: 1.03942
G1 F1887.634
G1 X135.197 Y124.862 E.11232
; LINE_WIDTH: 1.07405
G1 F1821.48
G1 X135.063 Y124.881 E.0218
; LINE_WIDTH: 1.09392
G1 F1785.573
G1 X134.487 Y124.979 E.09614
G1 X134.153 Y124.771 F30000
M204 S2000
; FEATURE: Top surface
; LINE_WIDTH: 0.831573
G1 F2413.736
G1 X129.781 Y120.399 E.75147
G1 X129.77 Y120.422 E.00314
G1 X128.579 Y120.251 E.14626
G1 X133.811 Y125.483 E.89917
G1 X133.756 Y126.483 E.12168
G1 X131.334 Y124.061 E.41622
G1 X131.334 Y123.324 E.08956
G1 X130.71 Y122.745 E.10353
G2 X129.223 Y121.95 I-2.659 J3.188 E.20626
G1 X127.356 Y120.083 E.32101
G1 X126.735 Y120.188 E.07647
G1 X126.744 Y120.284 E.01178
G1 X126.572 Y120.353 E.02257
G1 X127.989 Y121.771 E.24357
G2 X127.044 Y121.88 I.025 J4.356 E.11587
G1 X125.819 Y120.655 E.21053
G2 X125.104 Y120.995 I1.577 J4.239 E.09632
G1 X126.256 Y122.147 E.19795
G2 X125.58 Y122.526 I2.215 J4.737 E.09423
G1 X124.357 Y121.302 E.2103
G1 X123.999 Y121.599 E.05652
G1 X124.055 Y121.678 E.01179
G1 X123.889 Y121.889 E.03261
G1 X125.009 Y123.009 E.19243
G2 X124.529 Y123.583 I3.167 J3.133 E.0911
G1 X123.425 Y122.48 E.18971
G2 X122.995 Y123.105 I3.344 J2.758 E.0923
G1 X124.143 Y124.252 E.19729
G2 X123.877 Y125.041 I3.508 J1.623 E.10134
G1 X122.521 Y123.685 E.23305
G1 X122.334 Y124.189 E.06534
G1 X122.422 Y124.23 E.01179
G1 X122.371 Y124.589 E.04415
G1 X124.113 Y126.332 E.2995
M204 S10000
; WIPE_START
G1 F24000
G1 X122.699 Y124.918 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X130.331 Y124.796 Z10.4 F30000
G1 X131.004 Y124.785 Z10.4
G1 Z10
G1 E3 F1800
M204 S2000
G1 F2413.736
G1 X133.629 Y127.411 E.45128
G1 X133.578 Y127.77 E.04414
G1 X133.666 Y127.811 E.01179
G1 X133.479 Y128.315 E.06535
G1 X131.334 Y126.17 E.36863
G1 X131.334 Y127.225 E.12817
G1 X133.005 Y128.895 E.28714
G3 X132.575 Y129.521 I-3.773 J-2.133 E.0923
G1 X131.334 Y128.279 E.21332
G1 X131.334 Y128.676 E.04819
G1 X130.993 Y128.993 E.0566
G1 X132.111 Y130.111 E.19222
G1 X131.945 Y130.322 E.0326
G1 X132.001 Y130.401 E.01179
G1 X131.643 Y130.698 E.05653
G1 X130.418 Y129.473 E.21058
G3 X129.744 Y129.853 I-2.573 J-3.772 E.09419
G1 X130.896 Y131.005 E.198
G3 X130.181 Y131.345 I-2.291 J-3.899 E.09632
G1 X128.957 Y130.121 E.21043
G3 X128.011 Y130.23 I-.962 J-4.194 E.11593
G1 X129.428 Y131.647 E.24355
G1 X129.256 Y131.716 E.02256
G1 X129.265 Y131.812 E.01178
G1 X128.644 Y131.917 E.07648
G1 X126.779 Y130.053 E.32053
G3 X123.95 Y127.223 I1.198 J-4.028 E.50683
G1 X122.244 Y125.518 E.2932
G1 X122.189 Y126.517 E.12168
G1 X127.421 Y131.749 E.89915
G1 X126.23 Y131.578 E.14624
G1 X126.219 Y131.601 E.00315
G1 X121.847 Y127.229 E.75146
M204 S10000
G1 X121.514 Y127.021 F30000
; FEATURE: Gap infill
; LINE_WIDTH: 1.10273
G1 F1770.105
G1 X120.937 Y127.119 E.09699
; LINE_WIDTH: 1.07405
G1 F1821.482
G1 X120.803 Y127.138 E.0218
; LINE_WIDTH: 1.03941
G1 F1887.637
G1 X120.09 Y127.259 E.11232
; LINE_WIDTH: 1.02465
G1 F1917.316
G1 X119.377 Y127.379 E.11058
; WIPE_START
G1 F24000
G1 X120.09 Y127.259 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X119.843 Y122.883 Z10.4 F30000
G1 Z10
G1 E3 F1800
; LINE_WIDTH: 1.02466
G1 F1917.293
G1 X120.52 Y123.135 E.11058
; LINE_WIDTH: 1.03942
G1 F1887.623
M73 P97 R0
G1 X121.198 Y123.387 E.11232
; LINE_WIDTH: 1.07405
G1 F1821.484
G1 X121.324 Y123.437 E.0218
; LINE_WIDTH: 1.10272
G1 F1770.129
G1 X121.872 Y123.641 E.09697
; WIPE_START
G1 F24000
G1 X121.324 Y123.437 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X122.494 Y119.222 Z10.4 F30000
G1 Z10
G1 E3 F1800
; LINE_WIDTH: 1.02466
G1 F1917.294
G1 X122.955 Y119.779 E.11058
; LINE_WIDTH: 1.03942
G1 F1887.626
G1 X123.416 Y120.336 E.11232
; LINE_WIDTH: 1.07405
G1 F1821.485
G1 X123.499 Y120.442 E.0218
; LINE_WIDTH: 1.10272
G1 F1770.118
G1 X123.873 Y120.893 E.09698
; WIPE_START
G1 F24000
G1 X123.499 Y120.442 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X126.979 Y119.513 Z10.4 F30000
G1 Z10
G1 E3 F1800
; LINE_WIDTH: 1.10273
G1 F1770.11
G1 X126.881 Y118.937 E.09698
; LINE_WIDTH: 1.07405
G1 F1821.484
G1 X126.862 Y118.803 E.0218
; LINE_WIDTH: 1.03941
G1 F1887.64
G1 X126.741 Y118.09 E.11232
; LINE_WIDTH: 1.02465
G1 F1917.317
G1 X126.621 Y117.377 E.11058
; WIPE_START
G1 F24000
G1 X126.741 Y118.09 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X131.117 Y117.842 Z10.4 F30000
G1 Z10
G1 E3 F1800
; LINE_WIDTH: 1.00991
G1 F1947.914
G1 X130.865 Y118.52 E.10889
; LINE_WIDTH: 1.03942
G1 F1887.625
G1 X130.613 Y119.198 E.11237
; LINE_WIDTH: 1.07405
G1 F1821.483
G1 X130.563 Y119.324 E.0218
; LINE_WIDTH: 1.09392
G1 F1785.577
G1 X130.359 Y119.872 E.09613
; WIPE_START
G1 F24000
G1 X130.563 Y119.324 E-2.85
; WIPE_END
G1 E-.15 F1800
G1 X133.107 Y121.873 Z10.4 F30000
G1 Z10
G1 E3 F1800
; LINE_WIDTH: 1.09392
G1 F1785.569
G1 X133.558 Y121.499 E.09614
; LINE_WIDTH: 1.07405
G1 F1821.481
G1 X133.664 Y121.416 E.0218
; LINE_WIDTH: 1.03942
G1 F1887.633
G1 X134.221 Y120.955 E.11237
; LINE_WIDTH: 1.0099
G1 F1947.926
G1 X134.778 Y120.494 E.10889
; close powerlost recovery
M1003 S0
; WIPE_START
G1 F24000
G1 X134.221 Y120.955 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 72
M625
M106 S0
M106 P2 S0
M981 S0 P20000 ; close spaghetti detector
; FEATURE: Custom
; filament end gcode 
M106 P3 S0
;===== date: 20230428 =====================
M400 ; wait for buffer to clear
G92 E0 ; zero the extruder
G1 E-0.8 F1800 ; retract
G1 Z10.5 F900 ; lower z a little
G1 X65 Y245 F12000 ; move to safe pos 
G1 Y265 F3000

G1 X65 Y245 F12000
G1 Y265 F3000
M140 S0 ; turn off bed
M106 S0 ; turn off fan
M106 P2 S0 ; turn off remote part cooling fan
M106 P3 S0 ; turn off chamber cooling fan

G1 X100 F12000 ; wipe
; pull back filament to AMS
M620 S255
G1 X20 Y50 F12000
G1 Y-3
T255
G1 X65 F12000
G1 Y265
G1 X100 F12000 ; wipe
M621 S255
M104 S0 ; turn off hotend

M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
    M400 ; wait all motion done
    M991 S0 P-1 ;end smooth timelapse at safe pos
    M400 S3 ;wait for last picture to be taken
M623; end of "timelapse_record_flag"

M400 ; wait all motion done
M17 S
M17 Z0.4 ; lower z motor current to reduce impact if there is something in the bottom

    G1 Z110 F600
    G1 Z108

M400 P100
M17 R ; restore z current

G90
G1 X128 Y250 F3600

M220 S100  ; Reset feedrate magnitude
M201.2 K1.0 ; Reset acc magnitude
M73.2   R1.0 ;Reset left time magnitude
M1002 set_gcode_claim_speed_level : 0

M17 X0.8 Y0.8 Z0.5 ; lower motor current to 45% power
M73 P100 R0
; EXECUTABLE_BLOCK_END

