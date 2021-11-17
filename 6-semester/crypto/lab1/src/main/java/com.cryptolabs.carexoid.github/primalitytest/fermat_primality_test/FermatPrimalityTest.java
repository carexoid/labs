package com.cryptolabs.carexoid.github.primalitytest.fermat_primality_test;

import java.math.BigInteger;
import java.util.Random;

public class FermatPrimalityTest {

    public static boolean isProbablyPrime(BigInteger n, int certainty) {
        if (certainty <= 0) {
            return false;
        }

        if (n.compareTo(BigInteger.ONE) == 0) {
            return false;
        }
        if (n.compareTo(BigInteger.TWO) == 0) {
            return true;
        }

        for (int i = 0; i < certainty; i++) {
            BigInteger a = new BigInteger(n.bitLength(), new Random());
            a = a.mod(n.subtract(BigInteger.TWO)).add(BigInteger.TWO);
            if (!a.gcd(n).equals(BigInteger.ONE)) {
                return false;
            }
            if (!a.modPow(n.subtract(BigInteger.ONE), n).equals(BigInteger.ONE)) {
                return false;
            }
        }
        return true;
    }
}
