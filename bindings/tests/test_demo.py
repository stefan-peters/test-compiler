import cmc.spam
import cmc.hello

#cmc.spam.system("ls -la")

import unittest

class TestSequenceFunctions(unittest.TestCase):
	def test_me(self):
		self.assertEqual(cmc.hello.greet(), "hello, world")



if __name__ == '__main__':
    unittest.main()