# 这是一个将bin文件转换成pcd文件的demo

i=1;for x in your/input/data/*.bin; do build/bin2pcd --infile $x --outfile PCD_data/$i.pcd; let i=i+1; done
 
#for x in your/input/data/*.bin  这是一个循环遍历所有的输入bin文件，每次将一个bin文件传给x
#do build/bin2pcd 是运行前面生成的bin2pcd文件，路径根据实际情况调整
#--infile 是输入文件，--outfile 是输出文件 
#i 是输出文件的名称
