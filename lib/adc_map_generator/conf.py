
# +5 >--o
#       |
#       R1
#       |
#       o ------< ADC input
#       |
#       R2
#       |
#      ___

class Config:
    BCOEFFICIENT = 3950
    TEMPERATURENOMINAL = 25
    THERMISTORNOMINAL = 10000
    ADC_RANGE = 1023
    DAC_RANGE = 255
    SERIESRESISTOR = 10000
    DIR_PATH = "./"
    R1_IS_A_THERMISTOR = False
