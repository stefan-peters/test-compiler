unamestr=`uname`

if [[ "$unamestr" == 'Darwin' ]]; then 
  export PATH="~/Development/llvm/install/bin:$PATH"
fi
