from unittest import TestCase

import util


class Test(TestCase):
    def test_find_approx_key(self):
        a = {
            1: 123,
            4: 3456,
            8: 78490295
        }
        self.assertEqual(1, util.find_approx_key(a, 0))
        self.assertEqual(1, util.find_approx_key(a, 1))
        self.assertEqual(4, util.find_approx_key(a, 3))
        self.assertEqual(8, util.find_approx_key(a, 1000))

    def test_distance(self):
        self.assertEqual(4, util.distance(1, 5))
        self.assertEqual(4, util.distance(5, 1))
        self.assertEqual(6, util.distance(1, -5))
