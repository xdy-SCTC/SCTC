What is Sctc?
-------------

Sctc is a decentralized blockchain project built on Bitcoin's UTXO model, with support for Ethereum Virtual Machine based smart contracts, and secured by a proof of stake consensus model. It achieves this through the revolutionary Account Abstraction Layer which allows the EVM to communicate with Sctc's Bitcoin-like UTXO blockchain. For more general information about Sctc as well as links to join our community, go to http://www.wlwsz.com/

Welcome to the Sctc Ignition Main Network. This is the main network where the tokens hold value and should be guarded very carefully. If you are testing the network, or developing unstable software on Sctc, we highly recommend using either testnet or regtest mode. 

The major features of the Sctc network include:

1. Compatibility with the Ethereum Virtual Machine, which allows for compatibility with most existing Solidity based smart contracts. No special solidity compiler is required to deploy your smart contract to Sctc. 
2. A Proof of Stake consensus system which is optimized for Sctc's contract model. Any user can stake and help to secure the network. There is no voting, master nodes, or minimum amount required. There have been transactions as small as 2 Sctc that have created blocks in the past. 
3. The Decentralized Governance Protocol is completely implemented and functional, which allows certain network parameters to be modified without a fork or other network disruption. This currently controls parameters like block size, gas prices, etc. 
4. Uses the UTXO transaction model and is compatible with Bitcoin, allowing for existing tooling and workflows to be used with Sctc. This allows for the infamous SPV protocol to be used which is ideal for light wallets on mobile phones and IoT devices.


Building Sctc Core
----------

### Build on Ubuntu

    This is a quick start script for compiling Sctc on  Ubuntu


    sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils git cmake libboost-all-dev
    sudo apt-get install software-properties-common
    sudo add-apt-repository ppa:bitcoin/bitcoin
    sudo apt-get update
    sudo apt-get install libdb4.8-dev libdb4.8++-dev

    # If you want to build the Qt GUI:
    sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler qrencode

    git clone https://github.com/sctcproject/sctc --recursive
    cd sctc

    # Note autogen will prompt to install some more dependencies if needed
    ./autogen.sh
    ./configure 
    make -j2
    
### Build on CentOS

Here is a brief description for compiling Sctc on CentOS, for more details please refer to [the specific document](https://github.com/sctcproject/sctc/blob/master/doc/build-unix.md)

    # Compiling boost manually
    sudo yum install python-devel bzip2-devel
    git clone https://github.com/boostorg/boost.git
    cd boost
    git checkout boost-1.66.0
    git submodule update --init --recursive
    ./bootstrap.sh --prefix=/usr --libdir=/usr/lib64
    ./b2 headers
    sudo ./b2 -j4 install
    
    # Installing Dependencies for Sctc
    sudo yum install epel-release
    sudo yum install libtool libdb4-cxx-devel openssl-devel libevent-devel
    
    # If you want to build the Qt GUI:
    sudo yum install qt5-qttools-devel protobuf-devel qrencode-devel
    
    # Building Sctc
    git clone --recursive https://github.com/sctcproject/sctc.git
    cd sctc
    ./autogen.sh
    ./configure
    make -j4

### Build on OSX

The commands in this guide should be executed in a Terminal application.
The built-in one is located in `/Applications/Utilities/Terminal.app`.

#### Preparation

Install the OS X command line tools:

`xcode-select --install`

When the popup appears, click `Install`.

Then install [Homebrew](https://brew.sh).

#### Dependencies

    brew install cmake automake berkeley-db4 libtool boost --c++11 --without-single --without-static miniupnpc openssl pkg-config protobuf qt5 libevent imagemagick --with-librsvg qrencode

NOTE: Building with Qt4 is still supported, however, could result in a broken UI. Building with Qt5 is recommended.

#### Build Sctc Core

1. Clone the sctc source code and cd into `sctc`

        git clone --recursive https://github.com/sctcproject/sctc.git
        cd sctc

2.  Build sctc-core:

    Configure and build the headless sctc binaries as well as the GUI (if Qt is found).

    You can disable the GUI build by passing `--without-gui` to configure.

        ./autogen.sh
        ./configure
        make

3.  It is recommended to build and run the unit tests:

        make check

### Run

Then you can either run the command-line daemon using `src/sctcd` and `src/sctc-cli`, or you can run the Qt GUI using `src/qt/sctc-qt`

For in-depth description of Sparknet and how to use Sctc for interacting with contracts, please see [sparknet-guide](doc/sparknet-guide.md).

License
-------

Sctc is GPLv3 licensed.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/sctcproject/sctc/tags) are created
regularly to indicate new official, stable release versions of Sctc.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).

Developer IRC can be found on Freenode at #sctc-dev.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

There are also [regression and integration tests](/qa) of the RPC interface, written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/qa) are installed) with: `qa/pull-tester/rpc-tests.py`

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.

