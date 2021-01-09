#!/usr/bin/env bash

# A Bash script to build and install BxJsontools ex01 example on Ubuntu (16.04).

src_dir=$(pwd)
install_dir=$(pwd)/_install.d
build_dir=$(pwd)/_build.d

opwd=$(pwd)
function my_exit()
{
    local error_code=$1
    shift 1
    cd ${opwd}
    exit ${error_code}
}

bxjsontools_install_dir="../../_install.d"
if [ ! -d ${bxjsontools_install_dir} ]; then
    echo >&2 "[error] No BxJsontools installation! Abort!"
    my_exit 1
fi
cd ${bxjsontools_install_dir}
bxjsontools_install_dir=$(pwd)
echo >&2 "[info] BxJsontools install dir = '${bxjsontools_install_dir}'"
cd ${opwd}
export PATH="${bxjsontools_install_dir}/bin:${PATH}"

which bxjsontools-query > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo >&2 "[error] BxJsontools is not installed! Abort!"
    my_exit 1
fi


if [ -d ${install_dir} ]; then
    rm -fr ${install_dir}
fi

if [ -d ${build_dir} ]; then
    rm -fr ${build_dir}
fi

mkdir -p ${build_dir}

echo >&2 ""
echo >&2 "[info] Configuring..."
cd ${build_dir}
#    -DCMAKE_FIND_ROOT_PATH="$(bxjsontools-query --prefix)"
cmake \
    -DCMAKE_INSTALL_PREFIX="${install_dir}" \
    -DBxJsontools_DIR="$(bxjsontools-query --cmakedir)" \
    ${src_dir}
if [ $? -ne 0 ]; then
    echo >&2 "[error] CMake failed! Abort!"
    my_exit 1
fi

echo >&2 ""
echo >&2 "[info] Building..."
make -j4
if [ $? -ne 0 ]; then
    echo >&2 "[error] Build failed! Abort!"
    my_exit 1
fi

echo >&2 "[info] Build dir:"
tree ${build_dir}
echo >&2 ""

echo >&2 ""
echo >&2 "[info] Installing..."
make install
if [ $? -ne 0 ]; then
    echo >&2 "[error] Installation failed! Abort!"
    my_exit 1
fi

echo >&2 "[info] Installation dir:"
tree ${install_dir}
echo >&2 ""

my_exit 0

# end
