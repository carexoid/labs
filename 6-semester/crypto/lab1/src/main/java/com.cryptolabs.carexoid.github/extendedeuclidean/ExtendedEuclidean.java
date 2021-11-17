package com.cryptolabs.carexoid.github.extendedeuclidean;

import java.math.BigInteger;

public class ExtendedEuclidean {

    public static ExtendedEuclideanResult compute(BigInteger a, BigInteger b) {
        if (a.equals(BigInteger.ZERO)) {
            return new ExtendedEuclideanResult(
                    BigInteger.ZERO, BigInteger.ONE, b
            );
        }


        ExtendedEuclideanResult gcdResult = compute(b.mod(a), a);
        return new ExtendedEuclideanResult(
                gcdResult.BezoutY.subtract(b.divide(a).multiply(gcdResult.BezoutX)),
                gcdResult.BezoutX,
                gcdResult.gcd
        );
    }
}
