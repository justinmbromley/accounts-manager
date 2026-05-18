# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "src/core/CMakeFiles/accounts_core_autogen.dir/AutogenUsed.txt"
  "src/core/CMakeFiles/accounts_core_autogen.dir/ParseCache.txt"
  "src/core/accounts_core_autogen"
  "tests/core/CMakeFiles/test_account_autogen.dir/AutogenUsed.txt"
  "tests/core/CMakeFiles/test_account_autogen.dir/ParseCache.txt"
  "tests/core/CMakeFiles/test_account_summary_autogen.dir/AutogenUsed.txt"
  "tests/core/CMakeFiles/test_account_summary_autogen.dir/ParseCache.txt"
  "tests/core/test_account_autogen"
  "tests/core/test_account_summary_autogen"
  )
endif()
