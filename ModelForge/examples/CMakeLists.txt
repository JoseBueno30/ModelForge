# Lista de archivos .use
set(USE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/BankAccount.use
)

# Copiar archivos al directorio de compilación
file(COPY ${USE_FILES} DESTINATION ${CMAKE_BINARY_DIR}/examples)

# Opcional: Instalar archivos si usas 'make install'
install(FILES ${USE_FILES} DESTINATION share/examples)
