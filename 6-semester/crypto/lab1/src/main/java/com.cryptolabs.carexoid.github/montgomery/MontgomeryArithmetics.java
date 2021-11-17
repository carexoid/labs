package com.cryptolabs.carexoid.github.montgomery;

import com.cryptolabs.carexoid.github.extendedeuclidean.ExtendedEuclidean;
import com.cryptolabs.carexoid.github.extendedeuclidean.ExtendedEuclideanResult;

import java.math.BigInteger;

public class MontgomeryArithmetics {

    private static BigInteger redc(BigInteger a, BigInteger b, BigInteger n) {
        BigInteger r = BigInteger.TWO.shiftLeft(n.bitLength());
        ExtendedEuclideanResult euclideanResult = ExtendedEuclidean.compute(n, r); // compute r * r^(-1) - n * n` == 1

        BigInteger t = a.multiply(b);
        BigInteger m = t
                .multiply(euclideanResult.getBezoutX().negate())
                .and(r.subtract(BigInteger.ONE)); // m = t * n` mod r  (in binary operations)
        BigInteger u = t
                .add(m.multiply(n))
                .shiftRight(n.bitLength()); // u = (t + m * n) / r (with binary shifting)

        while (u.compareTo(n) >= 0) {
            u = u.subtract(n);
        }
        return u;
    }

    public static BigInteger modMultiply(BigInteger a, BigInteger b, BigInteger mod) {
        if (!mod.testBit(0) || mod.compareTo(BigInteger.ONE) <= 0) {
            throw new IllegalArgumentException("Mod should be a positive odd number");
        }
        BigInteger uModified = redc(
                a.shiftLeft(mod.bitLength()).mod(mod), // a * r mod n
                b.shiftLeft(mod.bitLength()).mod(mod), // b * r mod n
                mod
        );
        return redc(uModified, BigInteger.ONE, mod);
    }

    public static BigInteger modPower(BigInteger a, BigInteger power, BigInteger mod) {
        if (!mod.testBit(0) || mod.compareTo(BigInteger.ONE) <= 0) {
            throw new IllegalArgumentException("Mod should be a positive odd number");
        }
        BigInteger aModified = a.shiftLeft(mod.bitLength()).mod(mod);
        BigInteger xModified = BigInteger.ONE.shiftLeft(mod.bitLength()).mod(mod);
        for (int i = power.bitLength() - 1; i >= 0; i--) {
            xModified = redc(xModified, xModified, mod);
            if (power.testBit(i)) {
                xModified = redc(xModified, aModified, mod);
            }
        }

        return redc(xModified, BigInteger.ONE, mod);
    }
}
