# JarJarLibs


### Purpose:

`JarJarLibs` is a static analysis tool for Java that scans .jar files to identify native `(JNI)` method calls and maps out the Java methods that invoke them, directly or indirectly.


JarJarLibs helps 

- Locate all native (JNI) method calls inside .jar files

- Trace back and list all Java methods that eventually call these JNI functions

- Output a call graph in Graphviz DOT format for further analysis or visualization

<br>

### Usage:

```
        ▄▄▄██▀▀▀▄▄▄       ██▀███  ▄▄▄██▀▀▀▄▄▄       ██▀███   ██▓     ██▓ ▄▄▄▄     ██████ 
        ▒██  ▒████▄    ▓██ ▒ ██▒  ▒██  ▒████▄    ▓██ ▒ ██▒▓██▒    ▓██▒▓█████▄ ▒██    ▒ 
        ░██  ▒██  ▀█▄  ▓██ ░▄█ ▒  ░██  ▒██  ▀█▄  ▓██ ░▄█ ▒▒██░    ▒██▒▒██▒ ▄██░ ▓██▄   
    ▓██▄██▓ ░██▄▄▄▄██ ▒██▀▀█▄ ▓██▄██▓ ░██▄▄▄▄██ ▒██▀▀█▄  ▒██░    ░██░▒██░█▀    ▒   ██▒
    ▓███▒   ▓█   ▓██▒░██▓ ▒██▒▓███▒   ▓█   ▓██▒░██▓ ▒██▒░██████▒░██░░▓█  ▀█▓▒██████▒▒
    ▒▓▒▒░   ▒▒   ▓▒█░░ ▒▓ ░▒▓░▒▓▒▒░   ▒▒   ▓▒█░░ ▒▓ ░▒▓░░ ▒░▓  ░░▓  ░▒▓███▀▒▒ ▒▓▒ ▒ ░
    ▒ ░▒░    ▒   ▒▒ ░  ░▒ ░ ▒░▒ ░▒░    ▒   ▒▒ ░  ░▒ ░ ▒░░ ░ ▒  ░ ▒ ░▒░▒   ░ ░ ░▒  ░ ░
    ░ ░ ░    ░   ▒     ░░   ░ ░ ░ ░    ░   ▒     ░░   ░   ░ ░    ▒ ░ ░    ░ ░  ░  ░  
    ░   ░        ░  ░   ░     ░   ░        ░  ░   ░         ░  ░ ░   ░            ░  
                                                                            ░          
    Usage: ./jjl [options] input
    Options:
        -h, --help              show this help message
        -r, --recursive         recursively process all .jar files in the input directory
        -x, --exclude <regex>   exclude matching patterns (e.g. "lib|render|test|sql")
        -i, --include <regex>   include only matching patterns (e.g. "system|native")
        -j, --jni               start traversal from JNI methods
        -d, --depth <value>     maximum depth of function call recursion
        -o, --output <file>     output .dot file
```
<br>

```bash
./jjl -j -o outfile.dot javaArchive.jar | dot -Tpdf -o result.pdf
```
<br>

![image](./.img/dot.png)
<br>

### Credits:

This project is based on [Excse's ares_byte_code](https://github.com/Excse/ares_byte_code/) java class parser.
<br>

### Licence:

BSD 3-Clause License

Copyright (c) 2025, Charlie Beaufils

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
