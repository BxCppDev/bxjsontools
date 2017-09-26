#!/usr/bin/env bash

# A Bash script to build and install devel BxJsontools on Ubuntu (16.04).

opwd=$(pwd)
function my_exit()
{
    local error_code=$1
    shift 1
    cd ${opwd}
    exit ${error_code}
}

function my_usage()
{
    cat<<EOF

Options:

   --help             : print this help
   --boost-root path  : set the Boost installation base directory
   --brew             : use the Linuxbrew package manager

EOF
    return
}

src_dir=$(pwd)
install_dir=$(pwd)/_install.d
build_dir=$(pwd)/_build.d
boost_root=
brew_it=0

while [ -n "$1" ]; do
    tok="$1"
    if [ "${tok}" = "--help" ]; then
	my_usage
	exit 1
    elif [ "${tok}" = "--boost-root" ]; then
	shift 1
	boost_root="$1"
    elif [ "${tok}" = "--brew" ]; then
	brew_it=1
    else
	echo >&2 "[error] Invalid command line switch '${tok}'!"
	exit 1
    fi
    shift 1
done

if [ -d ${install_dir} ]; then
    rm -fr ${install_dir}
fi

if [ -d ${build_dir} ]; then
    rm -fr ${build_dir}
fi

if [ ${brew_it} -ne 0 ]; then
    #if [ -z "${boost_root}" ]; then
	boost_root=$(brew --prefix)
    #fi
fi
echo >&2 "[info] brew_it=${brew_it}"
echo >&2 "[info] boost_root=${boost_root}"

mkdir -p ${build_dir}

cd ${build_dir}
echo >&2 ""
echo >&2 "[info] Configuring..."
boost_option=
if [ -n "${boost_root}" ]; then
    boost_option="-DBOOST_ROOT=${boost_root}"
fi
echo >&2 "[info] boost_option=${boost_option}"

cmake \
    -DCMAKE_INSTALL_PREFIX="${install_dir}" \
    ${boost_option} \
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

echo >&2 ""
echo >&2 "[info] Installing..."
make install
if [ $? -ne 0 ]; then
    echo >&2 "[error] Installation failed! Abort!"
    my_exit 1
fi

my_exit 0

# end
