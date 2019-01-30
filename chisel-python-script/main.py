'''
Created on Jan 13, 2019

@author: wilkinmj
'''
import struct
import csv


def main():
    
    code = read_csv("32pointsConverted.csv")
    bundles = ["" for _ in range(29)];
    for x in range(28):
        bundles[x] += "val bundle" + str(x+1) +" = Wire(new VOSBundle())"
    for x in bundles:
        print(x)
    for x in code:
        print(x)
    
    file = open("output.txt","w") 
    
    for x in bundles:
        file.write(x + "\n") 
    for x in code:
        file.write(x + "\n")
    
    file.close()
    
def float_to_hex(num):
    return hex(struct.unpack('<I', struct.pack('<f', num))[0])
def read_csv(file_name):
    
    with open(file_name) as csv_file:
        table_strings = ["" for _ in range(84)];
        
        i = 0
        n = 1
        for x in range(84):
            if i == 0:
                table_strings[x] += "bundle" + str(n) + ".Vmem := VecInit(Array("
                i = 1
            elif i == 1:
                table_strings[x] += "bundle" + str(n) + ".offset := VecInit(Array(" 
                i = 2
            elif i == 2:
                table_strings[x] += "bundle" + str(n) + ".slope := VecInit(Array("
                i = 0
                n += 1
            
        csv_reader = csv.reader(csv_file, delimiter=',')
        line_count = 0;
        for row in csv_reader:
            column_count = 0
            for number in row:
                table_strings[line_count] = table_strings[line_count] + '"h' + str(float_to_hex(float(number)))[2:] + '".U(32.W),'
                if column_count == 31:
                    table_strings[line_count] = table_strings[line_count][:-1] + "))"
                column_count += 1
            line_count += 1;
    return table_strings
if __name__ == '__main__':
    main()