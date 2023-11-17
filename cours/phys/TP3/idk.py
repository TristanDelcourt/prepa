import numpy as np

fprime = [-30,-31,-28,-30,-34,-34]

moyenne = np.average(fprime)
ecart_type = np.std(fprime)
print(moyenne)
print(ecart_type)