# CMake generated Testfile for 
# Source directory: E:/Lab/TinyShader/include/jsoncpp/src/jsontestrunner
# Build directory: E:/Lab/TinyShader/build/include/jsoncpp/src/jsontestrunner
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(jsoncpp_readerwriter "D:/MiniConda/python.exe" "-B" "E:/Lab/TinyShader/include/jsoncpp/src/jsontestrunner/../../test/runjsontests.py" "E:/Lab/TinyShader/build/include/jsoncpp/src/jsontestrunner/jsontestrunner_exe.exe" "E:/Lab/TinyShader/include/jsoncpp/src/jsontestrunner/../../test/data")
set_tests_properties(jsoncpp_readerwriter PROPERTIES  WORKING_DIRECTORY "E:/Lab/TinyShader/include/jsoncpp/src/jsontestrunner/../../test/data" _BACKTRACE_TRIPLES "E:/Lab/TinyShader/include/jsoncpp/src/jsontestrunner/CMakeLists.txt;43;add_test;E:/Lab/TinyShader/include/jsoncpp/src/jsontestrunner/CMakeLists.txt;0;")
add_test(jsoncpp_readerwriter_json_checker "D:/MiniConda/python.exe" "-B" "E:/Lab/TinyShader/include/jsoncpp/src/jsontestrunner/../../test/runjsontests.py" "--with-json-checker" "E:/Lab/TinyShader/build/include/jsoncpp/src/jsontestrunner/jsontestrunner_exe.exe" "E:/Lab/TinyShader/include/jsoncpp/src/jsontestrunner/../../test/data")
set_tests_properties(jsoncpp_readerwriter_json_checker PROPERTIES  WORKING_DIRECTORY "E:/Lab/TinyShader/include/jsoncpp/src/jsontestrunner/../../test/data" _BACKTRACE_TRIPLES "E:/Lab/TinyShader/include/jsoncpp/src/jsontestrunner/CMakeLists.txt;47;add_test;E:/Lab/TinyShader/include/jsoncpp/src/jsontestrunner/CMakeLists.txt;0;")
