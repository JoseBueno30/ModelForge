enable_testing(true)

# add_executable(MetaEnum MetaEnumTest.cpp)
# add_test(NAME MetaEnum COMMAND MetaEnum)
# target_link_libraries(MetaEnum PRIVATE MetaModelLib antlr4Lib Qt${QT_VERSION_MAJOR}::Test Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core)

# add_executable(MetaAttribute MetaAttributeTest.cpp)
# add_test(NAME MetaAttribute COMMAND MetaAttribute)
# target_link_libraries(MetaAttribute PRIVATE MetaModelLib antlr4Lib Qt${QT_VERSION_MAJOR}::Test Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core)

function(SETUP_TESTS)
       foreach(_testname ${ARGN})
           add_executable(${_testname} ${_testname}Test.cpp )
           add_test(NAME ${_testname} COMMAND ${_testname})
           target_link_libraries(${_testname} PRIVATE MetaModelLib antlr4Lib Qt${QT_VERSION_MAJOR}::Test Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core)
       endforeach()
endfunction()

SETUP_TESTS(
   MetaEnum MetaAttribute MetaVariable MetaStateMachine MetaOperation MetaType
)
