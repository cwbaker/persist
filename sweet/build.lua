
command  = command or "build";
platform = platform or "msvc";
source = source or "";
target = target or "";
variant = variant or "debug";
version = version or os.date( "%Y.%m.%d %H:%M:%S "..platform.." "..variant );
jobs = jobs or 4;

package.path = root("build/lua/?.lua")..";"..root("build/lua/?/init.lua");
require "build";

setup {
    bin = root( "../bin" );
    lib = root( "../lib" );
    obj = root( "../obj" );
    include_directories = {
        root( ".." )
    };
};

buildfile "assert/assert.build";
buildfile "error/error.build";
buildfile "path/path.build";
buildfile "persist/persist.build";
buildfile "rtti/rtti.build";
buildfile "unit/unit.build";

AsciiDoc {
    id = "persist.html";
    "persist.txt"
}

build {};
