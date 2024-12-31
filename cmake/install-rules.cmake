install(
    TARGETS regex_exe
    RUNTIME COMPONENT regex_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
