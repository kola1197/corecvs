target_sources(corecvs
    PUBLIC
        kalman/cooSparseMatrix.h
        kalman/cholesky.h
        kalman/upperUnitaryMatrix.h
        kalman/uduDecomposed.h
    #    kalman/kalman.h
        kalman/classicKalman.h

    PRIVATE
        kalman/cooSparseMatrix.cpp
        kalman/cholesky.cpp
        kalman/upperUnitaryMatrix.cpp
        kalman/uduDecomposed.cpp
    #    kalman/kalman.cpp
        kalman/classicKalman.cpp
)

