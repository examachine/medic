echo Generating MEDIC base classes
echo Assuming %1 build of classgen

cd ..\..\classgen\autogen
echo In directory classgen\autogen
..\..\vc6\classgen\%1\classgen.exe ..\dictionaries\UIDDict.txt ..\dictionaries\TAGDict.txt ..\dictionaries\MODDict.txt ..\dictionaries\CIODDict.txt ..\dictionaries\NIODDict.txt ..\dictionaries\MESSAGEDict.txt ..\dictionaries\TAGDict2.txt ..\dictionaries\MODDict2.txt gxx

