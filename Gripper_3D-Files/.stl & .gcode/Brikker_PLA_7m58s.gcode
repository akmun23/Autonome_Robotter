; HEADER_BLOCK_START
; BambuStudio 01.08.04.51
; model printing time: 2m 3s; total estimated time: 7m 58s
; total layer number: 10
; model label id: 66
; filament_density: 1.24,1.24
; filament_diameter: 1.75,1.75
; max_z_height: 4.00
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
M73 P0 R7
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
M73 P54 R3
G1 X60 F12000
G1 Y245
G1 Y265 F3000
M620 M
M620 S0A   ; switch material if AMS exist
    M109 S220
    G1 X120 F12000

M73 P55 R3
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
G1 E5 F300
M109 S200 ; drop nozzle temp, make filament shink a bit
G92 E0
M73 P58 R3
G1 E-0.5 F300

M73 P62 R3
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
M73 P62 R2
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
G1 X100 F5000
G1 X70 F15000
M73 P63 R2
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
M73 P64 R2
G1 Z10
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
    G29 A X118 Y118 I20 J20
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
M73 P65 R2
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
; layer num/total_layer_count: 1/10
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
; start printing object, unique label id: 66
M624 AQAAAAAAAAA=
G1 X126.951 Y117.36 F30000
M73 P66 R2
G1 Z.4
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2100
G3 X128.283 Y117.303 I1.032 J8.599 E.15968
G3 X124.427 Y118.062 I-.292 J8.697 E6.068
G3 X126.832 Y117.375 I3.556 J7.897 E.30026
G1 X126.862 Y116.631 F30000
; FEATURE: Outer wall
G1 F2100
G3 X128.305 Y116.569 I1.119 J9.325 E.17295
M73 P67 R2
G3 X124.126 Y117.392 I-.314 J9.432 E6.58083
G3 X126.743 Y116.646 I3.856 J8.564 E.32681
; WIPE_START
G1 F24000
G1 X127.429 Y116.578 E-.98186
G1 X128.305 Y116.569 E-1.24854
M73 P68 R2
G1 X128.739 Y116.601 E-.6196
; WIPE_END
G1 E-.15 F1800
G1 X134.684 Y121.387 Z.8 F30000
G1 X135.356 Y121.928 Z.8
G1 Z.4
G1 E3 F1800
; FEATURE: Bottom surface
; LINE_WIDTH: 0.820466
M73 P69 R2
G1 F2450.23
G1 X133.711 Y120.283 E.27849
G2 X130.816 Y118.427 I-5.709 J5.719 E.4149
G1 X135.573 Y123.184 E.80536
G3 X135.958 Y124.608 I-7.179 J2.708 E.17697
M73 P70 R2
G1 X129.392 Y118.042 E1.11186
G2 X128.239 Y117.928 I-1.765 J11.981 E.13873
G1 X136.074 Y125.762 E1.32655
G3 X136.041 Y126.768 I-8.097 J.237 E.12057
G1 X127.232 Y117.959 E1.49153
G2 X126.331 Y118.097 I.775 J8.083 E.1092
G1 X135.903 Y127.669 E1.62076
G3 X135.685 Y128.491 I-8.617 J-1.845 E.10175
G1 X125.509 Y118.315 E1.72294
G2 X124.756 Y118.601 I1.987 J6.366 E.09649
G1 X135.399 Y129.244 E1.80201
G3 X135.053 Y129.936 I-8.308 J-3.716 E.09275
G1 X124.064 Y118.947 E1.86074
G2 X123.421 Y119.343 I4.786 J8.468 E.0904
G1 X134.657 Y130.58 E1.90248
G3 X134.207 Y131.168 I-9.143 J-6.526 E.08875
G1 X122.832 Y119.793 E1.92609
M73 P71 R2
G2 X122.286 Y120.286 I7.824 J9.206 E.08808
G1 X133.714 Y131.714 E1.93499
M73 P72 R2
G3 X133.168 Y132.207 I-4.35 J-4.265 E.08812
G1 X121.793 Y120.832 E1.92609
G2 X121.342 Y121.42 I8.688 J7.111 E.08875
G1 X132.58 Y132.658 E1.90264
G3 X131.936 Y133.053 I-3.593 J-5.119 E.09047
M73 P73 R2
G1 X120.947 Y122.064 E1.86073
G2 X120.602 Y122.758 I7.021 J3.918 E.09283
M73 P74 R2
G1 X131.244 Y133.399 E1.80177
G3 X130.491 Y133.685 I-2.74 J-6.081 E.09649
G1 X120.315 Y123.509 E1.72293
G2 X120.097 Y124.331 I8.4 J2.666 E.10176
G1 X129.669 Y133.903 E1.62075
G3 X128.768 Y134.041 I-1.676 J-7.944 E.1092
G1 X119.959 Y125.232 E1.49151
G2 X119.926 Y126.238 I8.063 J.768 E.12057
G1 X127.762 Y134.074 E1.32679
G3 X126.608 Y133.958 I.259 J-8.421 E.13899
G1 X120.042 Y127.392 E1.11183
G2 X120.427 Y128.816 I7.565 J-1.284 E.17698
G1 X125.184 Y133.573 E.80531
G3 X122.286 Y131.714 I2.807 J-7.565 E.41527
G1 X120.644 Y130.072 E.27806
; CHANGE_LAYER
; Z_HEIGHT: 0.8
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X122.058 Y131.486 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 66
M625
; layer num/total_layer_count: 2/10
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
; start printing object, unique label id: 66
M624 AQAAAAAAAAA=
G17
M73 P75 R1
G3 Z.8 I1.152 J.393 P1  F30000
G1 X126.933 Y117.21 Z.8
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2451.784
G3 X128.535 Y117.161 I1.071 J8.79 E.19203
G3 X129.067 Y134.791 I-.539 J8.839 E3.13567
G3 X126.814 Y117.225 I-1.064 J-8.791 E3.31325
G1 X126.844 Y116.48 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X127.421 Y116.428 E.0693
G3 X128.579 Y116.428 I.583 J9.572 E.13864
G3 X129.156 Y135.52 I-.584 J9.572 E3.39575
G3 X126.726 Y116.496 I-1.152 J-9.52 E3.58935
M204 S10000
; WIPE_START
G1 F24000
G1 X127.421 Y116.428 E-.99526
G1 X128 Y116.41 E-.82546
G1 X128.579 Y116.428 E-.82548
G1 X128.721 Y116.441 E-.2038
; WIPE_END
G1 E-.15 F1800
G1 X123.85 Y118.519 Z1.2 F30000
G1 Z.8
G1 E3 F1800
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.833514
G1 F2407.47
G1 X122.031 Y120.338 E.31345
G2 X120.282 Y123.144 I5.965 J5.666 E.40566
G1 X125.144 Y118.282 E.83781
G3 X126.591 Y117.892 I2.726 J7.239 E.18291
M73 P76 R1
G1 X119.892 Y124.591 E1.15436
G2 X119.776 Y125.765 I8.433 J1.428 E.14383
G1 X127.765 Y117.776 E1.37666
G3 X128.788 Y117.81 I.235 J8.256 E.12481
G1 X119.81 Y126.788 E1.54703
G2 X119.951 Y127.704 I8.237 J-.796 E.11306
G1 X129.705 Y117.951 E1.68073
G3 X130.54 Y118.173 I-1.872 J8.731 E.10537
G1 X120.173 Y128.54 E1.78645
G2 X120.464 Y129.306 I6.478 J-2.024 E.09994
G1 X131.306 Y118.464 E1.8683
G3 X132.011 Y118.817 I-3.808 J8.499 E.09607
G1 X120.817 Y130.011 E1.92907
G2 X121.22 Y130.666 I5.612 J-3.002 E.09371
G1 X132.666 Y119.22 E1.97245
G3 X133.265 Y119.678 I-6.687 J9.361 E.09193
G1 X121.678 Y131.265 E1.99671
G2 X122.18 Y131.82 I4.843 J-3.872 E.09128
G1 X133.82 Y120.18 E2.00592
G3 X134.322 Y120.735 I-8.88 J8.53 E.09124
G1 X122.735 Y132.322 E1.99671
G2 X123.334 Y132.78 I7.287 J-8.905 E.09193
G1 X134.78 Y121.334 E1.97246
G3 X135.183 Y121.989 I-5.209 J3.657 E.09371
M73 P77 R1
G1 X123.989 Y133.183 E1.92908
G2 X124.697 Y133.533 I3.611 J-6.419 E.09624
G1 X135.536 Y122.694 E1.86783
G3 X135.827 Y123.46 I-6.187 J2.79 E.09994
G1 X125.46 Y133.827 E1.78646
G2 X126.295 Y134.049 I2.708 J-8.509 E.10537
G1 X136.049 Y124.295 E1.68074
G3 X136.19 Y125.212 I-8.096 J1.713 E.11306
G1 X127.212 Y134.19 E1.54705
G2 X128.235 Y134.224 I.788 J-8.222 E.12481
G1 X136.224 Y126.235 E1.37668
G3 X136.108 Y127.409 I-8.548 J-.254 E.14383
G1 X129.409 Y134.108 E1.15439
G2 X130.856 Y133.718 I-1.278 J-7.628 E.1829
G1 X135.718 Y128.856 E.83785
G3 X133.971 Y131.66 I-7.603 J-2.79 E.40544
G1 X132.15 Y133.481 E.31381
; CHANGE_LAYER
; Z_HEIGHT: 1.2
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X133.564 Y132.067 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 66
M625
; layer num/total_layer_count: 3/10
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L3
M991 S0 P2 ;notify layer change
; start printing object, unique label id: 66
M624 AQAAAAAAAAA=
G17
G3 Z1.2 I1.111 J-.496 P1  F30000
G1 X126.933 Y117.213 Z1.2
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2451.784
G3 X128.167 Y117.15 I1.078 J8.906 E.14791
G3 X124.86 Y117.72 I-.176 J8.852 E6.25185
G3 X126.814 Y117.229 I3.152 J8.4 E.24162
G1 X126.845 Y116.48 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X127.421 Y116.43 E.06923
G3 X128.189 Y116.416 I.561 J9.527 E.0919
G3 X124.064 Y117.255 I-.198 J9.586 E6.70009
G3 X126.727 Y116.497 I3.918 J8.702 E.33244
M204 S10000
; WIPE_START
G1 F24000
G1 X127.421 Y116.43 E-.99367
M73 P78 R1
G1 X128.189 Y116.416 E-1.09423
G1 X128.579 Y116.428 E-.5562
G1 X128.723 Y116.441 E-.20589
; WIPE_END
G1 E-.15 F1800
G1 X134.681 Y121.211 Z1.6 F30000
G1 X135.488 Y121.857 Z1.6
G1 Z1.2
G1 E3 F1800
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.833514
G1 F2407.47
G1 X133.66 Y120.029 E.31506
G2 X130.856 Y118.282 I-5.595 J5.857 E.40544
G1 X135.718 Y123.144 E.83785
G3 X136.108 Y124.591 I-7.238 J2.725 E.1829
G1 X129.409 Y117.892 E1.15439
G2 X128.235 Y117.776 I-1.428 J8.432 E.14383
G1 X136.224 Y125.765 E1.37668
G3 X136.19 Y126.788 I-8.256 J.235 E.12481
G1 X127.212 Y117.81 E1.54705
G2 X126.295 Y117.951 I.796 J8.237 E.11306
G1 X136.049 Y127.705 E1.68074
G3 X135.827 Y128.54 I-8.73 J-1.872 E.10537
G1 X125.46 Y118.173 E1.78646
M73 P79 R1
G2 X124.694 Y118.464 I2.024 J6.479 E.09994
G1 X135.536 Y129.306 E1.86831
G3 X135.183 Y130.011 I-8.5 J-3.808 E.09607
G1 X123.989 Y118.817 E1.92908
G2 X123.334 Y119.22 I3.002 J5.612 E.09371
G1 X134.78 Y130.666 E1.97246
G3 X134.322 Y131.265 I-9.365 J-6.69 E.09193
G1 X122.735 Y119.678 E1.99671
G2 X122.18 Y120.18 I5.171 J6.275 E.09125
G1 X133.82 Y131.82 E2.00588
G3 X133.265 Y132.322 I-4.427 J-4.34 E.09128
G1 X121.678 Y120.735 E1.99671
G2 X121.22 Y121.334 I8.903 J7.286 E.09193
G1 X132.666 Y132.78 E1.97245
G3 X132.011 Y133.183 I-3.657 J-5.209 E.09371
G1 X120.817 Y121.989 E1.92907
G2 X120.464 Y122.694 I8.147 J4.512 E.09607
G1 X131.306 Y133.536 E1.8683
G3 X130.54 Y133.827 I-2.79 J-6.187 E.09994
G1 X120.173 Y123.46 E1.78645
G2 X119.951 Y124.296 I8.508 J2.707 E.10537
G1 X129.704 Y134.049 E1.68073
G3 X128.788 Y134.19 I-1.712 J-8.096 E.11306
G1 X119.81 Y125.212 E1.54703
G2 X119.776 Y126.235 I8.222 J.788 E.12481
G1 X127.765 Y134.224 E1.37666
G3 X126.591 Y134.108 I.255 J-8.549 E.14383
M73 P80 R1
G1 X119.892 Y127.409 E1.15436
G2 X120.282 Y128.856 I7.628 J-1.279 E.18291
G1 X125.144 Y133.718 E.83781
G3 X122.338 Y131.969 I2.791 J-7.604 E.40576
G1 X120.512 Y130.143 E.31468
; CHANGE_LAYER
; Z_HEIGHT: 1.6
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X121.926 Y131.557 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 66
M625
; layer num/total_layer_count: 4/10
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L4
M991 S0 P3 ;notify layer change
; start printing object, unique label id: 66
M624 AQAAAAAAAAA=
G17
G3 Z1.6 I1.149 J.401 P1  F30000
G1 X126.933 Y117.211 Z1.6
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F1352
G3 X128.247 Y117.152 I1.05 J8.746 E.15757
G3 X124.366 Y117.925 I-.256 J8.85 E6.17826
G3 X126.814 Y117.226 I3.617 J8.033 E.30569
G1 X126.843 Y116.48 F30000
M204 S5000
; FEATURE: Outer wall
G1 F1352
G1 X126.845 Y116.485 E.00059
G3 X128.269 Y116.418 I1.161 J9.579 E.17081
G3 X123.543 Y117.509 I-.278 J9.583 E6.62043
G3 X126.272 Y116.572 I4.463 J8.556 E.34651
G1 X126.724 Y116.499 E.05481
M204 S10000
; WIPE_START
G1 F24000
G1 X126.845 Y116.485 E-.17246
G1 X127.421 Y116.428 E-.82529
G1 X128.269 Y116.418 E-1.20905
G1 X128.579 Y116.428 E-.44143
G1 X128.72 Y116.44 E-.20177
; WIPE_END
G1 E-.15 F1800
G1 X124.642 Y122.892 Z2 F30000
G1 X120.515 Y129.42 Z2
G1 Z1.6
G1 E3 F1800
; FEATURE: Sparse infill
G1 F1352
G2 X122.18 Y131.82 I8.323 J-3.996 E.35101
G1 X133.82 Y120.18 E1.96967
G2 X122.18 Y120.18 I-5.82 J5.856 E1.54569
M73 P81 R1
G1 X133.82 Y131.82 E1.96967
G3 X131.42 Y133.485 I-6.397 J-6.657 E.35101
; CHANGE_LAYER
; Z_HEIGHT: 2
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X132.676 Y132.774 E-2.05676
G1 X133.103 Y132.418 E-.79324
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 66
M625
; layer num/total_layer_count: 5/10
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L5
M991 S0 P4 ;notify layer change
; start printing object, unique label id: 66
M624 AQAAAAAAAAA=
G17
G3 Z2 I1.128 J-.458 P1  F30000
G1 X126.933 Y117.21 Z2
G1 E3 F1800
; FEATURE: Inner wall
G1 F1376
G3 X128.535 Y117.161 I1.071 J8.79 E.19203
G3 X129.067 Y134.791 I-.539 J8.839 E3.13567
G3 X126.814 Y117.225 I-1.064 J-8.791 E3.31326
G1 X126.846 Y116.48 F30000
M204 S5000
; FEATURE: Outer wall
G1 F1376
G1 X127.421 Y116.431 E.0691
G3 X128.579 Y116.428 I.605 J9.681 E.13862
G3 X137.081 Y122.93 I-.59 J9.581 E1.35848
G1 X137.081 Y122.93 E0
G3 X131.07 Y135.081 I-9.081 J3.069 E1.80155
G1 X131.07 Y135.081 E0
G3 X118.919 Y129.07 I-3.069 J-9.081 E1.80155
G1 X118.919 Y129.07 E0
G3 X124.93 Y116.919 I9.081 J-3.069 E1.80155
G1 X124.93 Y116.919 E0
G3 X126.73 Y116.499 I3.096 J9.193 E.22145
M204 S10000
; WIPE_START
G1 F24000
G1 X127.421 Y116.431 E-.98989
G1 X128 Y116.41 E-.82535
M73 P82 R1
G1 X128.579 Y116.428 E-.82548
G1 X128.725 Y116.441 E-.20928
; WIPE_END
G1 E-.15 F1800
G1 X126.922 Y123.857 Z2.4 F30000
G1 X124.58 Y133.485 Z2.4
G1 Z2
G1 E3 F1800
; FEATURE: Sparse infill
G1 F1376
G3 X122.18 Y131.82 I3.538 J-7.662 E.3513
G1 X133.82 Y120.18 E1.96967
G3 X133.82 Y131.82 I-5.872 J5.82 E1.54511
G1 X122.18 Y120.18 E1.96967
G2 X120.515 Y122.58 I6.657 J6.397 E.35101
; CHANGE_LAYER
; Z_HEIGHT: 2.4
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X121.226 Y121.324 E-2.05673
G1 X121.582 Y120.897 E-.79327
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 66
M625
; layer num/total_layer_count: 6/10
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L6
M991 S0 P5 ;notify layer change
; start printing object, unique label id: 66
M624 AQAAAAAAAAA=
G17
G3 Z2.4 I.691 J1.002 P1  F30000
G1 X126.933 Y117.21 Z2.4
G1 E3 F1800
; FEATURE: Inner wall
G1 F1717
G3 X128.408 Y117.157 I1.052 J8.734 E.17687
M73 P83 R1
G3 X125.366 Y117.546 I-.417 J8.843 E6.2862
G3 X126.814 Y117.225 I2.619 J8.398 E.17768
G1 X126.846 Y116.48 F30000
M204 S5000
; FEATURE: Outer wall
G1 F1717
G1 X127.421 Y116.432 E.06903
G3 X128.43 Y116.423 I.59 J9.58 E.1208
G3 X134.673 Y119.117 I-.437 J9.591 E.83151
G1 X134.673 Y119.117 E0
G3 X137.585 Y125.851 I-6.656 J6.876 E.90095
G1 X137.585 Y125.851 E0
G3 X128.149 Y135.585 I-9.585 J.149 E1.80173
G1 X128.149 Y135.585 E0
G3 X121.327 Y132.883 I-.144 J-9.598 E.9008
G1 X121.327 Y132.883 E0
G3 X118.415 Y126.149 I6.632 J-6.865 E.90108
G1 X118.415 Y126.149 E0
G3 X126.731 Y116.5 I9.597 J-.137 E1.66657
M204 S10000
; WIPE_START
G1 F24000
G1 X127.421 Y116.432 E-.98801
M73 P84 R1
G1 X128 Y116.41 E-.8253
G1 X128.43 Y116.423 E-.61359
G1 X128.726 Y116.446 E-.4231
; WIPE_END
G1 E-.15 F1800
G1 X128.374 Y117.78 Z2.8 F30000
G1 Z2.4
G1 E3 F1800
; FEATURE: Sparse infill
G1 F1717
G3 X135.965 Y123.934 I-.377 J8.224 E1.2518
G1 X135.965 Y123.934 E0
G3 X135.419 Y129.556 I-7.978 J2.063 E.68982
G1 X135.419 Y129.556 E0
G3 X120.2 Y123.384 I-7.42 J-3.554 E2.9718
G1 X120.2 Y123.384 E0
G3 X125.934 Y118.035 I7.797 J2.611 E.97808
G1 X125.934 Y118.035 E0
G3 X128.254 Y117.777 I2.036 J7.747 E.28027
G1 X134.92 Y123.126 F30000
G1 F1717
G2 X133.297 Y120.703 I-7.206 J3.072 E.35103
G1 X122.703 Y131.297 E1.79252
G2 X133.301 Y131.301 I5.301 J-5.293 E1.40851
G1 X122.699 Y120.699 E1.7939
M73 P85 R1
G1 X122.816 Y120.589 E.01917
G3 X125.126 Y119.08 I5.188 J5.418 E.3321
; CHANGE_LAYER
; Z_HEIGHT: 2.8
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X124.516 Y119.362 E-.95786
G1 X123.741 Y119.831 E-1.29006
G1 X123.415 Y120.098 E-.60208
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 66
M625
; layer num/total_layer_count: 7/10
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L7
M991 S0 P6 ;notify layer change
; start printing object, unique label id: 66
M624 AQAAAAAAAAA=
G17
G3 Z2.8 I.772 J.94 P1  F30000
G1 X126.933 Y117.209 Z2.8
G1 E3 F1800
; FEATURE: Inner wall
G1 F1784
G3 X128.489 Y117.159 I1.091 J9.762 E.18648
G3 X126.814 Y117.224 I-.496 J8.84 E6.45522
G1 X126.841 Y116.481 F30000
M204 S5000
; FEATURE: Outer wall
G1 F1784
G1 X126.844 Y116.482 E.00039
G3 X128.511 Y116.426 I1.156 J9.518 E.19977
G3 X137.588 Y125.932 I-.518 J9.581 E1.7324
G1 X137.588 Y125.932 E0
G3 X128.068 Y135.588 I-9.588 J.068 E1.80201
G1 X128.068 Y135.588 E0
G3 X126.339 Y135.443 I-.11 J-9.084 E.20796
G1 X126.339 Y135.443 E0
G3 X118.412 Y126.068 I1.661 J-9.443 E1.59409
G1 X118.412 Y126.068 E0
G3 X118.557 Y124.339 I9.084 J-.11 E.20796
G1 X118.557 Y124.339 E0
G3 X126.272 Y116.569 I9.443 J1.661 E1.39432
G1 X126.723 Y116.499 E.05461
M204 S10000
; WIPE_START
G1 F24000
G1 X126.844 Y116.482 E-.1749
G1 X127.421 Y116.428 E-.8254
G1 X128 Y116.41 E-.82548
G1 X128.511 Y116.426 E-.72836
G1 X128.718 Y116.443 E-.29586
; WIPE_END
G1 E-.15 F1800
M73 P86 R1
G1 X128.453 Y117.783 Z3.2 F30000
G1 Z2.8
G1 E3 F1800
; FEATURE: Sparse infill
G1 F1784
G3 X122.767 Y132.349 I-.453 J8.216 E3.71724
G1 X122.767 Y132.349 E0
G3 X128.333 Y117.779 I5.233 J-6.349 E2.45379
G1 X125.126 Y132.92 F30000
G1 F1784
G3 X122.699 Y131.301 I2.849 J-6.899 E.35136
G1 X133.301 Y120.699 E1.7939
G3 X133.301 Y131.301 I-5.348 J5.301 E1.40721
G1 X122.699 Y120.699 E1.7939
G3 X125.126 Y119.08 I5.679 J5.883 E.35098
; CHANGE_LAYER
; Z_HEIGHT: 3.2
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X124.516 Y119.362 E-.95786
G1 X123.741 Y119.831 E-1.29007
G1 X123.417 Y120.101 E-.60208
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 66
M625
; layer num/total_layer_count: 8/10
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L8
M991 S0 P7 ;notify layer change
; start printing object, unique label id: 66
M624 AQAAAAAAAAA=
G17
G3 Z3.2 I.773 J.94 P1  F30000
G1 X126.933 Y117.21 Z3.2
G1 E3 F1800
; FEATURE: Inner wall
G1 F2451.784
G3 X128.535 Y117.161 I1.071 J8.79 E.19203
G3 X129.067 Y134.791 I-.539 J8.839 E3.13567
G3 X126.814 Y117.225 I-1.064 J-8.791 E3.31326
G1 X126.847 Y116.48 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X127.421 Y116.428 E.06891
M73 P87 R1
G3 X128.579 Y116.428 I.583 J9.572 E.13864
G3 X129.156 Y135.52 I-.584 J9.572 E3.39575
G3 X126.728 Y116.496 I-1.152 J-9.52 E3.58966
M204 S10000
; WIPE_START
G1 F24000
G1 X127.421 Y116.428 E-.99151
G1 X128 Y116.41 E-.82546
G1 X128.579 Y116.428 E-.82548
G1 X128.724 Y116.441 E-.20756
; WIPE_END
G1 E-.15 F1800
G1 X131.086 Y123.699 Z3.6 F30000
G1 X133.862 Y132.227 Z3.6
G1 Z3.2
G1 E3 F1800
; FEATURE: Bridge
; LINE_WIDTH: 0.809432
; LAYER_HEIGHT: 0.8
G1 F1399.207
G1 X135.271 Y129.727 E.60172
M73 P87 R0
G2 X136.161 Y126.401 I-7.178 J-3.702 E.72753
G1 X132.565 Y132.777 E1.53476
G3 X131.149 Y133.538 I-4.243 J-6.194 E.33776
G1 X136.08 Y124.795 E2.10459
G2 X135.796 Y123.549 I-6.858 J.907 E.26835
G1 X129.935 Y133.94 E2.50126
G3 X128.844 Y134.126 I-2.052 J-8.733 E.23236
G1 X135.391 Y122.518 E2.79422
G2 X134.904 Y121.632 I-7.639 J3.621 E.21211
G1 X127.833 Y134.168 E3.01754
G3 X126.888 Y134.094 I.197 J-8.609 E.19884
G1 X134.352 Y120.861 E3.18525
G2 X133.745 Y120.188 I-7.642 J6.284 E.1901
G1 X125.998 Y133.923 E3.30599
G3 X125.159 Y133.662 I1.739 J-7.068 E.18442
M73 P88 R0
G1 X133.087 Y119.605 E3.38351
G2 X132.382 Y119.105 I-5.838 J7.485 E.18122
G1 X124.366 Y133.317 E3.42088
G3 X123.618 Y132.895 I3.724 J-7.478 E.18027
G1 X131.633 Y118.683 E3.42088
G2 X130.841 Y118.338 I-4.177 J8.522 E.18122
G1 X122.913 Y132.395 E3.3835
G3 X122.255 Y131.812 I4.493 J-5.729 E.18442
G1 X130.002 Y118.077 E3.30598
G2 X129.112 Y117.906 I-2.314 J9.622 E.1901
G1 X121.648 Y131.139 E3.18524
G3 X121.096 Y130.368 I6.715 J-5.394 E.19885
G1 X128.167 Y117.832 E3.01752
G2 X127.156 Y117.874 I-.157 J8.452 E.21211
G1 X120.609 Y129.482 E2.79419
G3 X120.204 Y128.451 I8.13 J-3.792 E.23237
G1 X126.065 Y118.06 E2.50122
G2 X124.851 Y118.462 I1.559 J6.74 E.26835
G1 X119.92 Y127.205 E2.10454
G3 X119.839 Y125.599 I7.416 J-1.179 E.33777
G1 X123.435 Y119.223 E1.53468
G2 X121.048 Y121.707 I4.496 J6.711 E.72783
G1 X119.639 Y124.205 E.60131
; CHANGE_LAYER
; Z_HEIGHT: 3.6
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X120.621 Y122.463 E-2.85
; WIPE_END
M73 P89 R0
G1 E-.15 F1800
; stop printing object, unique label id: 66
M625
; layer num/total_layer_count: 9/10
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L9
M991 S0 P8 ;notify layer change
; start printing object, unique label id: 66
M624 AQAAAAAAAAA=
G17
G3 Z3.6 I.77 J.943 P1  F30000
G1 X126.944 Y117.3 Z3.6
G1 E3 F1800
; FEATURE: Inner wall
; LINE_WIDTH: 0.82
G1 F2451.784
G3 X128.184 Y117.238 I1.066 J8.812 E.14873
G3 X124.891 Y117.802 I-.193 J8.764 E6.18785
G3 X126.825 Y117.315 I3.119 J8.31 E.23909
G1 X126.856 Y116.567 F30000
M204 S5000
; FEATURE: Outer wall
G1 F2451.784
G1 X127.426 Y116.518 E.06853
G3 X128.206 Y116.504 I.584 J10.313 E.09334
G3 X131.022 Y116.995 I-.141 J9.12 E.34342
G1 X131.022 Y116.995 E0
G3 X126.737 Y116.582 I-3.031 J9.004 E6.6225
M204 S10000
; WIPE_START
G1 F24000
G1 X127.426 Y116.518 E-.987
G1 X128.206 Y116.504 E-1.11139
G1 X128.574 Y116.515 E-.52393
G1 X128.733 Y116.529 E-.22769
; WIPE_END
G1 E-.15 F1800
G1 X134.681 Y121.312 Z4 F30000
G1 X135.411 Y121.899 Z4
G1 Z3.6
G1 E3 F1800
; FEATURE: Internal solid infill
; LINE_WIDTH: 0.825919
G1 F2432.176
M73 P90 R0
G1 X133.69 Y120.177 E.29364
G2 X130.833 Y118.367 I-5.945 J6.222 E.41065
G1 X135.633 Y123.167 E.81886
G3 X136.021 Y124.601 I-7.203 J2.715 E.17944
G1 X129.399 Y117.979 E1.12954
G2 X128.236 Y117.863 I-1.419 J8.357 E.141
M73 P91 R0
G1 X136.137 Y125.764 E1.34754
G3 X136.103 Y126.777 I-8.163 J.236 E.12233
G1 X127.223 Y117.897 E1.51461
G2 X126.316 Y118.036 I.784 J8.147 E.1108
G1 X135.964 Y127.684 E1.6457
G3 X135.744 Y128.511 I-8.662 J-1.856 E.10326
G1 X125.489 Y118.256 E1.74935
G2 X124.73 Y118.544 I2.002 J6.413 E.09792
G1 X135.456 Y129.27 E1.82957
G3 X135.108 Y129.968 I-8.388 J-3.755 E.09413
G1 X124.032 Y118.892 E1.88915
G2 X123.384 Y119.291 I2.971 J5.555 E.09182
G1 X134.709 Y130.616 E1.93167
G3 X134.255 Y131.209 I-9.234 J-6.593 E.09007
M73 P92 R0
G1 X122.791 Y119.745 E1.95545
G2 X122.242 Y120.242 I7.889 J9.282 E.08939
G1 X133.758 Y131.758 E1.96448
G3 X133.209 Y132.255 I-4.382 J-4.296 E.08943
G1 X121.745 Y120.791 E1.95545
G2 X121.291 Y121.384 I8.776 J7.183 E.09007
G1 X132.616 Y132.709 E1.93166
G3 X131.968 Y133.108 I-3.619 J-5.156 E.09182
G1 X120.892 Y122.032 E1.88914
G2 X120.544 Y122.73 I8.039 J4.452 E.09413
G1 X131.27 Y133.456 E1.82957
G3 X130.511 Y133.744 I-2.761 J-6.125 E.09792
G1 X120.256 Y123.489 E1.74934
G2 X120.036 Y124.316 I8.444 J2.683 E.10326
G1 X129.684 Y133.964 E1.64568
G3 X128.776 Y134.103 I-1.691 J-8.008 E.1108
G1 X119.897 Y125.224 E1.51459
G2 X119.863 Y126.237 I8.129 J.777 E.12233
G1 X127.763 Y134.137 E1.34752
G3 X126.601 Y134.021 I.257 J-8.474 E.141
G1 X119.979 Y127.399 E1.12951
G2 X120.367 Y128.833 I7.591 J-1.281 E.17944
G1 X125.167 Y133.633 E.81882
G3 X122.308 Y131.821 I2.785 J-7.555 E.41136
G1 X120.589 Y130.102 E.29325
; CHANGE_LAYER
; Z_HEIGHT: 4
; LAYER_HEIGHT: 0.4
; WIPE_START
G1 F24000
G1 X122.003 Y131.516 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 66
M625
; layer num/total_layer_count: 10/10
M622.1 S1 ; for prev firware, default turned on
M1002 judge_flag timelapse_record_flag
M622 J1
 ; timelapse without wipe tower
M971 S11 C10 O0

M623
; update layer progress
M73 L10
M991 S0 P9 ;notify layer change
; start printing object, unique label id: 66
M624 AQAAAAAAAAA=
G17
G3 Z4 I1.154 J.386 P1  F30000
G1 X126.894 Y116.887 Z4
G1 E3 F1800
M204 S5000
; FEATURE: Outer wall
; LINE_WIDTH: 0.82
G1 F2451.784
G3 X128.182 Y116.821 I1.117 J9.233 E.15454
G1 X128.182 Y116.821 E0
G3 X124.743 Y117.413 I-.192 J9.18 E6.4828
G3 X126.774 Y116.902 I3.268 J8.708 E.25112
M204 S10000
; WIPE_START
G1 F24000
G1 X127.445 Y116.833 E-.96133
M73 P93 R0
G1 X128.182 Y116.821 E-1.05027
G1 X128.182 Y116.821 E0
G1 X128.555 Y116.833 E-.53048
G1 X128.77 Y116.852 E-.30792
; WIPE_END
G1 E-.15 F1800
G1 X130.352 Y124.319 Z4.4 F30000
G1 X132.35 Y133.749 Z4.4
G1 Z4
G1 E3 F1800
M204 S2000
; FEATURE: Top surface
; LINE_WIDTH: 0.829761
G1 F2419.615
G1 X134.161 Y131.938 E.31054
G2 X135.998 Y129.048 I-6.241 J-5.997 E.41788
G1 X131.048 Y133.998 E.84866
G3 X129.584 Y134.411 I-2.973 J-7.745 E.18477
G1 X136.411 Y127.584 E1.17058
G2 X136.548 Y126.395 I-6.229 J-1.32 E.14533
G1 X128.395 Y134.548 E1.39796
G3 X127.358 Y134.533 I-.385 J-9.206 E.1258
G1 X136.533 Y125.358 E1.57317
G2 X136.413 Y124.426 I-10.877 J.926 E.11398
G1 X126.426 Y134.413 E1.71242
G3 X125.579 Y134.207 I1.276 J-7.099 E.10567
G1 X136.207 Y123.579 E1.8223
G2 X135.935 Y122.799 I-8.801 J2.635 E.10018
G1 X124.799 Y133.935 E1.90934
M73 P94 R0
G3 X124.076 Y133.606 I2.36 J-6.139 E.09636
G1 X135.606 Y122.076 E1.97682
G2 X135.221 Y121.41 I-9.138 J4.835 E.09339
G1 X123.41 Y133.221 E2.02509
G3 X122.789 Y132.789 I3.261 J-5.342 E.09168
G1 X134.789 Y120.79 E2.05735
G2 X134.308 Y120.218 I-8.029 J6.269 E.09055
G1 X122.218 Y132.308 E2.07286
G3 X121.692 Y131.782 I4.085 J-4.611 E.09025
G1 X133.782 Y119.692 E2.07286
G2 X133.21 Y119.211 I-6.842 J7.549 E.09055
G1 X121.211 Y131.21 E2.05734
G3 X120.779 Y130.59 I4.91 J-3.881 E.09168
G1 X132.59 Y118.779 E2.02509
G2 X131.924 Y118.394 I-5.499 J8.749 E.09339
G1 X120.394 Y129.924 E1.97681
G3 X120.065 Y129.201 I5.81 J-3.083 E.09636
G1 X131.201 Y118.065 E1.90933
G2 X130.421 Y117.793 I-3.414 J8.528 E.10018
G1 X119.793 Y128.421 E1.82229
G3 X119.587 Y127.574 I6.894 J-2.122 E.10568
G1 X129.574 Y117.587 E1.7124
G2 X128.642 Y117.467 I-1.858 J10.759 E.11398
G1 X119.467 Y126.642 E1.57315
G3 X119.452 Y125.605 I9.193 J-.652 E.1258
G1 X127.603 Y117.454 E1.39755
G2 X126.416 Y117.589 I.066 J5.872 E.14508
G1 X119.589 Y124.416 E1.17055
G3 X120.002 Y122.951 I8.156 J1.508 E.18477
G1 X124.951 Y118.002 E.84861
G2 X122.06 Y119.841 I3.108 J8.079 E.41823
G1 X120.251 Y121.65 E.31012
M204 S10000
; close powerlost recovery
M1003 S0
; WIPE_START
G1 F24000
G1 X121.665 Y120.236 E-2.85
; WIPE_END
G1 E-.15 F1800
; stop printing object, unique label id: 66
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
G1 Z4.5 F900 ; lower z a little
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
M73 P95 R0
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

    G1 Z104 F600
    G1 Z102

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

