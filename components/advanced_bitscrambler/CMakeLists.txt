# this compunent is written by Srdjan Crnjanski 2026 V1.0
# all rights reserved
# to use component for free you must NOT change any comment, author name, year and version number 

idf_component_register(SRCS "advanced_bitscrambler.c" 
                       INCLUDE_DIRS "include"
                       REQUIRES esp_driver_bitscrambler
                       )

target_bitscrambler_add_src("advanced_alu_sim_bga.bsasm")

