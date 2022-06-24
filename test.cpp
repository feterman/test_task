#define BOOST_TEST_MODULE main test suite

#include <filesystem>
#include <fstream>
#include <string>

#include <boost/test/unit_test.hpp>

#include "functions.hpp"

//Использовал тесты буста, потому что они у меня уже были и я ранее ими пользовался
ы
void writeFile(const std::filesystem::path& path, const std::string& data)
{
    std::ofstream file(path, std::ofstream::binary);
    if (!file.is_open()) {
        throw std::ofstream::failure{ "Failed to create file." };
    }
    file.write(data.c_str(), data.size());
}


BOOST_AUTO_TEST_CASE(read_file)
{
    std::string file_name{"text"};
    std::string str{"EGkwmve \n esf\t\t \'\'\'\"rsgin rsei "};
    writeFile(file_name, str);
    auto res = readFile(file_name);

    BOOST_CHECK(res);
    BOOST_CHECK(res.value() == str);


    std::filesystem::remove(file_name);
}


BOOST_AUTO_TEST_CASE(read_empty_file)
{
    std::string file_name{"empty"};
    writeFile(file_name, "");
    auto res = readFile(file_name);

    BOOST_CHECK(res);
    BOOST_CHECK(res.value() == "");

    std::filesystem::remove(file_name);
}


BOOST_AUTO_TEST_CASE(read_not_exist_file)
{
    std::string file_name{"testxt"};
    auto res = readFile(file_name);

    BOOST_CHECK(!res);
}


BOOST_AUTO_TEST_CASE(split_words)
{
    std::vector<std::string> words{"Eiebmowpv \te", "$90g3mDV 3rfm$) ", "30f sdi5m 3dk"};
    std::string str;
    for(const auto& word : words){
        str += word + '\n';
    }
    auto words2 = split(str);

    BOOST_CHECK(words.size() == words2.size());
    bool res{true};
    for(auto i = 0; i < words.size(); i++){
        res = res & (words[i] == words2[i]);
    }
    BOOST_CHECK(res);
}


BOOST_AUTO_TEST_CASE(split_empty)
{
    auto res = split("");
    BOOST_CHECK(res.empty());
}


BOOST_AUTO_TEST_CASE(split_one_word)
{
    std::string str{"rgjbRnV$($grnmv #) m49$v r4$"};
    auto words = split(str);

    BOOST_CHECK(words.size() == 1);
    BOOST_CHECK(str == words[0]);
}


BOOST_AUTO_TEST_CASE(compare_1)
{
    std::string str1{"rgn i$646gj $^)252 rgdrbrdtn"};
    std::string str2{str1};

    BOOST_CHECK(!compareString(str1, str2));
    BOOST_CHECK(!compareString(str2, str1));
}


BOOST_AUTO_TEST_CASE(compare_2)
{
    std::string str1{"rgn i$646gj $^)252 rgdrbrdtn"};
    std::string str2{str1 + '2'};

    BOOST_CHECK(compareString(str1, str2));
}


BOOST_AUTO_TEST_CASE(compare_3)
{
    std::string str1{"SRIKIBBWBRHERHEOODJBDRGRNM"};
    std::string str2{str1};
    for(std::size_t i = 0; i < str2.size(); i += 2){
        str2[i] = std::tolower(str2[i]);
    }
    
    BOOST_CHECK(!compareString(str1, str2));
    BOOST_CHECK(!compareString(str2, str1));
}


BOOST_AUTO_TEST_CASE(compare_empty_strings)
{
    std::string str1, str2;
    
    BOOST_CHECK(!compareString(str1, str2));
    BOOST_CHECK(!compareString(str2, str1));
}


BOOST_AUTO_TEST_CASE(delete_word_1)
{
    std::string str1{"ELGKKRGE kmsmeg4esi3vn 39gsv39 vese3ef.ioj"};
    std::string word{"ABra"};
    std::string str2{str1};

    str2.insert(3, word);
    str2.insert(10, word);
    str2.insert(20, word);
    deleteWord(str2, word);

    BOOST_CHECK(str2 == str1);
}


BOOST_AUTO_TEST_CASE(delete_word_empty_1)
{
    std::string str1{"ELGKKRGE kmsmeg4esi3vn 39gsv39 vese3ef.ioj"};
    std::string word{""};
    std::string str2{str1};

    deleteWord(str2, word);

    BOOST_CHECK(str2 == str1);
}


BOOST_AUTO_TEST_CASE(delete_word_empty_2)
{
    std::string str{""};
    std::string word{"Eebwe4gm"};

    deleteWord(str, word);

    BOOST_CHECK(str == "");
}


BOOST_AUTO_TEST_CASE(delete_word_empty_3)
{
    std::string str{""};
    std::string word{""};

    deleteWord(str, word);

    BOOST_CHECK(str == "");
}


BOOST_AUTO_TEST_CASE(save_result)
{
    std::vector<std::string> words{"srgoG4o4v 4wet40vv", "v303tv #)^vr4$Qv4 494$", "f JG$$  49t4V #$J($44#0"};
    std::string file_name{"TESTex"};
    std::string res1{""};

    for(const auto& word : words){
        res1 += word + '\n';
    }

    saveResult(file_name, words);
    auto res2 = readFile(file_name);

    BOOST_CHECK(res2);
    BOOST_CHECK(res1 == res2.value());

    std::filesystem::remove(file_name);
}


BOOST_AUTO_TEST_CASE(save_result_one_word)
{
    std::vector<std::string> words{"srgoG4o4v 4wet40vv"};
    std::string file_name{"TESTex"};
    std::string res1{""};

    for(const auto& word : words){
        res1 += word + '\n';
    }

    saveResult(file_name, words);
    auto res2 = readFile(file_name);

    BOOST_CHECK(res2);
    BOOST_CHECK(res1 == res2.value());

    std::filesystem::remove(file_name);
}


BOOST_AUTO_TEST_CASE(save_result_empty)
{
    std::vector<std::string> words;
    std::string file_name{"TESTex"};
    std::string res1{""};

    saveResult(file_name, words);
    auto res2 = readFile(file_name);

    BOOST_CHECK(res2);
    BOOST_CHECK(res1 == res2.value());

    std::filesystem::remove(file_name);
}