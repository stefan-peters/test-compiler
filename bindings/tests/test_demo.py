import cmc.spam
import cmc.hello

#cmc.spam.system("ls -la")

import unittest

class TestSequenceFunctions(unittest.TestCase):
	def test_me(self):
		self.assertEqual(cmc.hello.greet(), "hello, world")

	def test_mt(self):
		#self.assertFalse(cmc.hello.parse_string("invalid source code"))
		self.assertTrue(cmc.hello.parse_string("class ValidSourceCode {};"))

	def test_e(self):
		e = cmc.hello.Entity()
		e.name = "hallo"
		print(e.name)



if __name__ == '__main__':
    unittest.main()