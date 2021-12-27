
local paths = {
    package.path;
    root( 'lalr/src/lalr/?.lua' );
    root( 'lalr/src/lalr/?/init.lua' );
};
package.path = table.concat( paths, ";" );

variant = lower( variant or 'debug' );

local cc = require 'forge.cc' {
    identifier = 'cc_${platform}_${architecture}';
    platform = operating_system();
    bin = root( ('%s/bin'):format(variant) );
    lib = root( ('%s/lib'):format(variant) );
    obj = root( ('%s/obj'):format(variant) );
    include_directories = {
        root();
        root( 'lalr/src' );
        root( 'unittest-cpp' );
    };
    library_directories = {
        root( ("%s/lib"):format(variant) );
    };
    defines = {
        ('BUILD_OS_%s'):format( upper(operating_system()) );
        ('BUILD_VARIANT_%s'):format( upper(variant) );
        variant ~= 'shipping' and '_DEBUG' or 'NDEBUG';
    };
    zero_brane_studio = {
        mobdebug = mobdebug;
    };

    architecture = 'native';
    assertions = variant ~= 'shipping';
    debug = variant ~= 'shipping';
    debuggable = variant ~= 'shipping';
    exceptions = true;
    fast_floating_point = variant ~= 'debug';
    incremental_linking = variant == 'debug';
    link_time_code_generation = variant == 'shipping';
    lua_mobdebug_enabled = variant ~= 'shipping';
    minimal_rebuild = variant == 'debug';
    optimization = variant ~= 'debug';
    persist_test_enabled = true;
    run_time_checks = variant == 'debug';
    runtime_library = variant == 'debug' and 'static_debug' or 'static_release';
    run_time_type_info = true;
    standard = 'c++17';
    string_pooling = variant == 'shipping';
    strip = false;
    unit_tests_enabled = true;
    warning_level = 3;
    warnings_as_errors = true;
};

cc:install( require('forge.lalr') );

cc:all {
    'persist/persist_examples/all';
    'persist/persist_test/all';
};

buildfile 'lalr/lalr.forge';
buildfile 'persist.forge';
buildfile 'unittest-cpp/unittest-cpp.forge';
