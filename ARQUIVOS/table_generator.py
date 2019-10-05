#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from operator import add

def single_file():
    i=1
    try:
        input_file = open(sys.argv[1], "r")
        output_file = open(sys.argv[1]+'_out', "w")
    except IOError:
        print "Could not open/create file."
        return
    with input_file as inp:
        with output_file as outp:
            header(outp)
            while True:
                line = inp.readline().rstrip('\n')
                lista = line.split(',')
                if lista != ['']:
                    if lista[0]=='-':
                        outp.write( "%s & %s & %s & %s & %s & %s \\\\\n" % (str(i), '-', '-', '-', '-', '-') )
                    else:
                        outp.write( "%s & %s & %s & %s & %s & %s \\\\\n" % (str(i), lista[0], lista[1], '{:.7f}'.format(float(lista[2])), lista[3], lista[4]) )
                    i+=1
                else:
                    break
            footer(outp)
            print("done")
            inp.close()
            outp.close()

def multiples_files():
    try:
        output_file = open('bigtable_out', "w")
    except IOError:
        print "Could not create output file."
        return
    with output_file as outp:
        header(outp)
        for i in sys.argv[1::]:
            lista = [0,0,0,0,0]
            (lista, count) = aux_mult(i, lista)
            lista = map(lambda x: x/float(count), lista)
            print(count)
            outp.write( "%s & %s & %s & %s & %s & %s \\\\\n" % (i, lista[0], lista[1], '{:.7f}'.format(float(lista[2])), lista[3], lista[4]) )
        footer(outp)
        outp.close()

def aux_mult(file_name, l1):
    i=0
    try:
        input_file = open(file_name, "r")
    except IOError:
        print "Could not open file."
        raise Exception("ERRO in file %s" % file_name)
    with input_file as inp:
        while True:
            line = inp.readline().rstrip('\n')
            lista = line.split(',')
            if lista != ['']:
                i+=1
                lista = map(int, lista)
                l1 = map(add, l1, lista)
            else:
                break
        inp.close()
        return (l1, i)



def main():
    if(len(sys.argv) > 2): #tem mais de 1 arquivo, a tabela vai ter 1 linha por arquivo
        multiples_files()
    else:
        single_file()

def header(arq):
    arq.write('\\begin{longtable}[c]{@{}cccccc@{}}\n')
    arq.write('\\toprule\n')
    arq.write('\multicolumn{1}{c}{} & \multicolumn{1}{c}{Nodos Expandidos} & \multicolumn{1}{c}{Comprimento Sol.} & \multicolumn{1}{c}{Tempo} & \multicolumn{1}{c}{H Média} & \multicolumn{1}{c}{H Inicial} \\\\* \midrule \endhead \n')

def footer(arq):
    arq.write('* \\bottomrule\n')
    arq.write('\end{longtable}\n')


if __name__ == "__main__":
    main()