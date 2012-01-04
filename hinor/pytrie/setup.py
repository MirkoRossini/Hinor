from distutils.core import setup, Extension

module1 = Extension('hinor',
                    sources = ['../char_trie.c','pytrie.c'],
                    include_dirs = ['../'],
                    )

setup (name = 'PyTrie',
       version = '0.1',
       description = 'Package that adds trie feature to python. It also handles autocompletion.',
       ext_modules = [module1])