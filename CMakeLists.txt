cmake_minimum_required(VERSION 3.5)

project(barrel LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core LinguistTools REQUIRED)

set(TS_FILES barrel_en_US.ts)

add_executable(barrel
    src/main.cpp

    src/BarrelParser.cpp

    src/instructions/AccumulatorAccessor.cpp
    src/instructions/BarrelString.cpp
    src/instructions/BitShift.cpp
    src/instructions/ContinueStatement.cpp
    src/instructions/DecrementAccumulator.cpp
    src/instructions/DivideStatement.cpp
    src/instructions/EqualityOperation.cpp
    src/instructions/EqualTo.cpp
    src/instructions/ExitStatement.cpp
    src/instructions/FuzzyEqualTo.cpp
    src/instructions/FuzzyNotEqualTo.cpp
    src/instructions/GreaterThan.cpp
    src/instructions/GreaterThanEqualTo.cpp
    src/instructions/IfElse.cpp
    src/instructions/IncrementAccumulator.cpp
    src/instructions/Infinity.cpp
    src/instructions/InputStatement.cpp
    src/instructions/InstructionChain.cpp
    src/instructions/InstructionNode.cpp
    src/instructions/JumpStatement.cpp
    src/instructions/JumpTarget.cpp
    src/instructions/LessThan.cpp
    src/instructions/LessThanEqualTo.cpp
    src/instructions/Loop.cpp
    src/instructions/MultiplyStatement.cpp
    src/instructions/NegateAccumulator.cpp
    src/instructions/NotEqualTo.cpp
    src/instructions/Number.cpp
    src/instructions/PopFromStack.cpp
    src/instructions/PopLocationPointer.cpp
    src/instructions/PrimalityTest.cpp
    src/instructions/PrintStatement.cpp
    src/instructions/PushLocationPointer.cpp
    src/instructions/PushToStack.cpp
    src/instructions/RaiseAccToPower.cpp
    src/instructions/RandomNumberGenerator.cpp
    src/instructions/ReciprocateAccumulator.cpp
    src/instructions/RegisterAccessor.cpp
    src/instructions/SetAccumulator.cpp
    src/instructions/SetRegister.cpp
    src/instructions/SquareRootAcc.cpp
    src/instructions/StackAccessor.cpp

    ${TS_FILES}
)
target_link_libraries(barrel Qt5::Core)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
