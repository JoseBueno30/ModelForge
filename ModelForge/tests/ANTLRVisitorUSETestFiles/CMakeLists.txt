# Lista de archivos .use
set(USE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/classDefinition_undefinedSuperClass.use
    ${CMAKE_CURRENT_SOURCE_DIR}/invariant_undefinedScopeClass.use
    ${CMAKE_CURRENT_SOURCE_DIR}/prePostDefinition_undefinedScopeClass.use
    ${CMAKE_CURRENT_SOURCE_DIR}/prePostDefinition_undefinedScopeOperation.use
    ${CMAKE_CURRENT_SOURCE_DIR}/prePostDefinition_differentReturnTypeThanScopeOperation.use
    ${CMAKE_CURRENT_SOURCE_DIR}/prePostDefinition_differentNumberOfParametersThanScopeOperation.use
    ${CMAKE_CURRENT_SOURCE_DIR}/prePostDefinition_differentNameOfParameterThanScopeOperation.use
    ${CMAKE_CURRENT_SOURCE_DIR}/prePostDefinition_differentTypeOfParameterThanScopeOperation.use
    ${CMAKE_CURRENT_SOURCE_DIR}/simpleType_undefinedTypeName.use
    ${CMAKE_CURRENT_SOURCE_DIR}/associationClassDefinition_undefinedSuperClass.use
    ${CMAKE_CURRENT_SOURCE_DIR}/redefinesAssociationEnd_undefinedRedefinedAssociationEnd.use
    ${CMAKE_CURRENT_SOURCE_DIR}/subsetsAssociationEnd_undefinedSubsettedAssociationEnd.use
    ${CMAKE_CURRENT_SOURCE_DIR}/associationEndDefinition_undefinedClass.use
    ${CMAKE_CURRENT_SOURCE_DIR}/duplicateClassDefinition.use

)

# Copiar archivos al directorio de compilación
file(COPY ${USE_FILES} DESTINATION ${CMAKE_BINARY_DIR}/tests/ANTLRVisitorUSETestFiles)

# Opcional: Instalar archivos si usas 'make install'
install(FILES ${USE_FILES} DESTINATION share/ANTLRVisitorUSETestFiles)

