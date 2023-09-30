all: final_project.cpp Basic.cpp DP_Select.cpp map.cpp search_keyword.cpp alphabet_sequence.cpp advanced_search.cpp
	g++ -g final_project.cpp Basic.cpp DP_Select.cpp map.cpp search_keyword.cpp alphabet_sequence.cpp advanced_search.cpp -o final.out
	
clean: final.out final.out.dSYM
	rm -rf final.out final.out.dSYM
