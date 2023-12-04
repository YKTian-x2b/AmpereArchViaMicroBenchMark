import os
import re
import sys
import subprocess
import math

sys.path.append('/opt/kaiProjects/cuda_libs/CuAssembler-master/CuAsm')

import CubinFile
import CuInsAssemblerRepos
import CuInsFeeder
import CuAsmParser
import CuAsmLogger

class CuAsmTemplate:
    def __init__(self, template_name):
        self.m_FileParts = []
        self.m_MarkerDict = {}

        p = re.compile(r'@CUASM_INSERT_MARKER_POS\.(\w+)')

        with open(template_name) as fin:
            # print(f'Loading template file {template_name}...')
            buf = ''
            iline = 0
            for line in fin:
                iline += 1
                res = p.search(line)
                if res is not None:
                    # push buf in and reset buf
                    self.m_FileParts.append(buf)
                    buf = ''

                    marker = res.groups()[0]
                    if marker in self.m_MarkerDict:
                        print(f'  Duplicate marker "{marker}" in line {iline:d}')
                    else:
                        # print(f'  New marker "{marker}" in line {iline:d}')
                        self.m_MarkerDict[marker] = None
                    
                    self.m_FileParts.append((marker, line))
                else:
                    buf += line

            self.m_FileParts.append(buf)

    def setMarker(self, marker, s):
        self.m_MarkerDict[marker] = s
    
    def resetAllMarkers(self):
        for k in self.m_MarkerDict:
            self.m_MarkerDict[k] = None

    def generate(self, outfile):
        with open(outfile, 'w') as fout:
            for p in self.m_FileParts:
                if isinstance(p, str):
                    fout.write(p)
                elif isinstance(p, tuple):
                    marker, orig_line = p

                    # original line is always written back
                    fout.write(orig_line)
                    if self.m_MarkerDict[marker] is not None:
                        fout.write(self.m_MarkerDict[marker])
                        fout.write('\n') # ensure a newline after the insertion


def cubin2cuasm(binname, asmname=None):
    cf = CubinFile.CubinFile(binname)
    
    if asmname is None:
        if binname.endswith('.cubin'):
            asmname = binname.replace('.cubin', '.cuasm')
        else:
            asmname = binname + '.cuasm'
            
    cf.saveAsCuAsm(asmname)


def cuasm2cubin(asmname, binname=None):
    cap = CuAsmParser.CuAsmParser()
    cap.parse(asmname)
    if binname is None:
        if asmname.endswith('.cuasm'):
            binname = asmname.replace('.cuasm', '.cubin')
        else:
            binname = asmname + '.cubin'

    cap.saveAsCubin(binname)

