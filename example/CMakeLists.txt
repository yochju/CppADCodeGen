# --------------------------------------------------------------------------
#  CppADCodeGen: C++ Algorithmic Differentiation with Source Code Generation:
#    Copyright (C) 2012 Ciengis
#
#  CppADCodeGen is distributed under multiple licenses:
#
#   - Eclipse Public License Version 1.0 (EPL1), and
#   - GNU General Public License Version 3 (GPL3).
#
#  EPL1 terms and conditions can be found in the file "epl-v10.txt", while
#  terms and conditions for the GPL3 can be found in the file "gpl3.txt".
# ----------------------------------------------------------------------------
#
# Author: Joao Leal
#
# ----------------------------------------------------------------------------

################################################################################
#                             source_generation_c
################################################################################
ADD_EXECUTABLE(source_generation_c source_generation_c.cpp)
SET(EXAMPLES_COMMAND "COMMAND source_generation_c")
ADD_CUSTOM_TARGET(example_source_generation_c
                  COMMAND source_generation_c)

################################################################################
#                             source_generation_mathml
################################################################################
ADD_EXECUTABLE(source_generation_mathml source_generation_mathml.cpp)
SET(EXAMPLES_COMMAND "COMMAND source_generation_mathml")
ADD_CUSTOM_TARGET(example_source_generation_mathml
                  COMMAND source_generation_mathml)

################################################################################
#                             source_generation_latex
################################################################################
ADD_EXECUTABLE(source_generation_latex source_generation_latex.cpp)
SET(EXAMPLES_COMMAND "COMMAND source_generation_latex")
ADD_CUSTOM_TARGET(example_source_generation_latex
                  COMMAND source_generation_latex)

IF(PDFLATEX_COMPILER)
    ADD_DEFINITIONS(-DPDFLATEX_COMPILER="${PDFLATEX_COMPILER}")
ENDIF()

link_file("${CMAKE_CURRENT_SOURCE_DIR}/latex_template.tex"
          "${CMAKE_CURRENT_BINARY_DIR}/latex_template.tex")

# copy template (if required)
ADD_CUSTOM_TARGET(link_or_copy_latex_template
                  DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/latex_template.tex")
ADD_DEPENDENCIES(source_generation_latex link_or_copy_latex_template)

################################################################################
#                             source_generation_dot
################################################################################
ADD_EXECUTABLE(source_generation_dot source_generation_dot.cpp)
SET(EXAMPLES_COMMAND "COMMAND source_generation_dot")
ADD_CUSTOM_TARGET(example_source_generation_dot
                  COMMAND source_generation_dot)

IF(GRAPHVIZ_DOT_PATH)
    ADD_DEFINITIONS(-DGRAPHVIZ_DOT_PATH="${GRAPHVIZ_DOT_PATH}")
ENDIF()

IF(UNIX)
    ############################################################################
    #                                  dynamic_linux
    ############################################################################
    ADD_EXECUTABLE(dynamic_linux dynamic_linux.cpp)
    SET(EXAMPLES_COMMAND "${EXAMPLES_COMMAND} COMMAND dynamic_linux")
    TARGET_LINK_LIBRARIES(dynamic_linux ${DL_LIBRARIES})
    ADD_CUSTOM_TARGET(example_dynamic_linux
                      COMMAND dynamic_linux)

    ############################################################################
    #                                  lagrangian
    ############################################################################
    ADD_EXECUTABLE(lagrangian lagrangian.cpp)
    SET(EXAMPLES_COMMAND "${EXAMPLES_COMMAND} COMMAND lagrangian")
    TARGET_LINK_LIBRARIES(lagrangian ${DL_LIBRARIES})
    ADD_CUSTOM_TARGET(example_lagrangian
                      COMMAND lagrangian)

    ############################################################################
    #                                   patterns
    ############################################################################
    ADD_EXECUTABLE(patterns patterns.cpp)
    SET(EXAMPLES_COMMAND "${EXAMPLES_COMMAND} COMMAND patterns")
    TARGET_LINK_LIBRARIES(patterns ${DL_LIBRARIES})
    ADD_CUSTOM_TARGET(example_patterns
                      COMMAND patterns)
ENDIF(UNIX)


ADD_CUSTOM_TARGET(examples)
                  
ADD_DEPENDENCIES(examples example_source_generation_c)
ADD_DEPENDENCIES(examples example_source_generation_latex)
ADD_DEPENDENCIES(examples example_source_generation_mathml)
ADD_DEPENDENCIES(examples example_source_generation_dot)
IF(UNIX)
    ADD_DEPENDENCIES(examples example_dynamic_linux)
    ADD_DEPENDENCIES(examples example_lagrangian)
ENDIF()
