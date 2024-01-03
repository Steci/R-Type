# CMakeLists.txt in the tests directory

# Ajouter les fichiers source des tests
file(GLOB CLIENT_TEST_SOURCES "tests/client/*.cpp")
file(GLOB SERVER_TEST_SOURCES "tests/server/*.cpp")
file(GLOB ENGINE_TEST_SOURCES "tests/engine/*.cpp")

# Créer les exécutables de test
add_executable(client_tests ${CLIENT_TEST_SOURCES})
add_executable(server_tests ${SERVER_TEST_SOURCES})
add_executable(engine_tests ${ENGINE_TEST_SOURCES})

# Inclure le répertoire des en-têtes de votre projet
target_include_directories(client_tests PUBLIC ${EXTRA_INCLUDES})
target_include_directories(server_tests PUBLIC ${EXTRA_INCLUDES})
target_include_directories(engine_tests PUBLIC ${EXTRA_INCLUDES})

# Lier les bibliothèques nécessaires (votre code, Google Test, et autres)
target_link_libraries(client_tests PRIVATE gtest gtest_main pthread)
target_link_libraries(server_tests PRIVATE gtest gtest_main pthread)
target_link_libraries(engine_tests PRIVATE gtest gtest_main pthread)

# Enregistrer les tests avec CTest
gtest_discover_tests(client_tests)
gtest_discover_tests(server_tests)
gtest_discover_tests(engine_tests)
