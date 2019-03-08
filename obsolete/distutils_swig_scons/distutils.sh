#swig -python example.i
python setup.py clean 
#python setup.py build_ext 
python setup.py install --prefix=dist/ 
