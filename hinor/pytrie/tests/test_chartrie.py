#!/usr/bin/python

from hinor import CharTrie
import unittest

class TestCharTrieBasicFunctions(unittest.TestCase):

    def setUp(self):
      self.trie = CharTrie()
      #some dummy values
      self.trie.add("a")
      self.trie.add("b","c")
    def test_add(self):
      self.trie.add("justkey")                                                                                                                                          
      self.trie.add("key","val")                                                                                                                                                          
      self.trie.add("key2","val2")                                                                                                                                                          
      
    def test_get(self):
      s = self.trie.get("a")
      self.assertTrue(self.trie.get("a") == None)
      self.assertTrue(self.trie.get("Z") == None)
      self.trie.add("ZZ")
      self.assertTrue(self.trie.get("Z") == None)
      self.assertTrue(self.trie.get("b") == 'c')

    def test_autocomp(self):
      self.assertTrue(self.trie.autocomp("b") == 'b:c,')
      
  
if __name__ == '__main__':
    unittest.main()


