cmake_minimum_required(VERSION 3.25.1)
project(omni_alerts)

include(CTest)
include(CheckIncludeFile)

list(PREPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/../../cmake)

enable_testing()

find_package(PostgreSQL REQUIRED)

add_postgresql_extension(
        omni_alerts
        VERSION 0.1
        SCHEMA omni_alerts
        RELOCATABLE false
        SCRIPTS omni_alerts--0.1.sql
        SOURCES omni_alerts.c
)
