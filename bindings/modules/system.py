import subprocess
import os


def system_includes(compiler):

    lang = "c"
    if "++" in compiler:
        lang = "c++"

    cmd = "{0} -v -x \"{1}\" /dev/null -fsyntax-only".format(compiler, lang)
    p = subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, shell=True)
    output, err = p.communicate()

    includes = []
    do_read = False

    for line in output.split("\n"):
        if "search starts here" in line:
            do_read = True
        elif "End of search list" in line:
            do_read = False
        elif do_read:
            includes.append(line.strip())
    return [os.path.abspath(include) for include in includes if os.path.exists(include)]
