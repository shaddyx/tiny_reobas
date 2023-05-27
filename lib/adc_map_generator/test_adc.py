from unittest import TestCase

import adc
import conf


class TestAdc(TestCase):
    def test_adc_to_resistance(self):
        cnf = conf.Config()
        cnf.THERMISTORNOMINAL = 100000
        cnf.SERIESRESISTOR = 100000
        cnf.ADC_RANGE = 1024
        cnf.R1_IS_A_THERMISTOR = True
        ad = adc.Adc(cnf)
        self.assertEqual(100000, int(ad.adc_to_resistance(512)))
        self.assertEqual(924000, int(ad.adc_to_resistance(100)))
        self.assertEqual(999999, int(ad.adc_to_resistance(10)))

    def test_adc_to_resistance_r2(self):
        cnf = conf.Config()
        cnf.THERMISTORNOMINAL = 100000
        cnf.SERIESRESISTOR = 100000
        cnf.ADC_RANGE = 1024
        cnf.R1_IS_A_THERMISTOR = False
        ad = adc.Adc(cnf)
        self.assertEqual(100391, int(ad.adc_to_resistance(512)))
        self.assertEqual(10942, int(ad.adc_to_resistance(100)))
        self.assertEqual(1085, int(ad.adc_to_resistance(10)))

    def test_adc_to_resistance_r2_unbalanced(self):
        cnf = conf.Config()
        cnf.THERMISTORNOMINAL = 100000
        cnf.SERIESRESISTOR = 90000
        cnf.ADC_RANGE = 1024
        cnf.R1_IS_A_THERMISTOR = False
        ad = adc.Adc(cnf)
        self.assertEqual(90352, int(ad.adc_to_resistance(512)))
        self.assertEqual(9848, int(ad.adc_to_resistance(100)))
        self.assertEqual(977, int(ad.adc_to_resistance(10)))

    def test_adc_to_resistance_1000(self):
        cnf = conf.Config()
        cnf.THERMISTORNOMINAL = 10000
        cnf.SERIESRESISTOR = 1000
        cnf.ADC_RANGE = 1024
        cnf.R1_IS_A_THERMISTOR = True
        ad = adc.Adc(cnf)
        self.assertEqual(1000, int(ad.adc_to_resistance(512)))
        self.assertEqual(9240, int(ad.adc_to_resistance(100)))
        self.assertEqual(101400, int(ad.adc_to_resistance(10)))
        self.assertEqual(999999, int(ad.adc_to_resistance(0)))


