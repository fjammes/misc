#swig -python example.i
python setup.py build_ext --prefix=dist/ 
python setup.py install --prefix=dist/ 
