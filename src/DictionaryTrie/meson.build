# Define dictionary_trie using function library()

inc = include_directories('.')

dictionary_trie_dep = declare_dependency(include_directories: inc,
  link_with: dictionary_trie)

dictionary_trie = library('dictionary_trie', source: ['DictionaryTrie.cpp', 
							'DitionaryTrie.hpp'])
