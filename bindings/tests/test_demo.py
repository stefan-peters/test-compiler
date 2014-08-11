import cmc.spam
import cmc.hello

#cmc.spam.system("ls -la")

import unittest

class TestSequenceFunctions(unittest.TestCase):
	def test_me(self):
		self.assertEqual(cmc.hello.greet(), "hello, world")

	def test_mt(self):
		self.assertFalse(cmc.hello.parse_string("classx c {};"))
		self.assertTrue(cmc.hello.parse_string("class c {};"))



if __name__ == '__main__':
    unittest.main()