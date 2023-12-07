<HTML>

<BODY>

  <?php

  //
  // A low-memory way to scan for primes. The Sieve of Aristothenes
  // would be quite a bit faster, but you have to allocate such a
  // large buffer that it wouldn't be practical (unless you could do
  // bit-wise operations, which I don't think you can in PHP).
  //
  // So...just start at the bottom and check each number to see if
  // it is prime (well, not *every* number...we can skip the even
  // ones and the ones that end with '5').
  //
  // Written by: Erik Bryant
  // Date: December 12, 2003
  //

  function printprimes($primes)
  {
    print "<br>\n";
    $count = 0;
    foreach ($primes as $val) {
      print "$val, ";
      $count++;
      if ($count == 10) {
        print "<br>\n";
        $count = 0;
      }
    }
    print "<br>\n";
  }

  $chunks = explode(" ", microtime());
  $time_start = $chunks[0] + $chunks[1];
  unset($chunks);
  print "Time: $time_start<br><br>\n";

  //
  // A number is prime if it is not divisible by
  // any of the primes below it.
  //
  function isprime($num, $ctr)
  {
    foreach ($ctr as $val) {
      if ($num % $val == 0) return (0);
    }

    return (1);
  }

  //
  // When we find a prime number, we don't need to immediately
  // start checking it against new candidates. In fact, we won't
  // need prime 'p' until we reach candidate 'c' such that
  // c = p*p. So, as we find primes, we store them on a queue
  // to be added to the checklist later. This function grabs
  // the next prime off of the queue and adds it to the
  // checklist. Note that the candidate '$i' must therefore
  // be equal to the square of that prime, so $i is not
  // prime itself.
  //
  function qchk($i, &$qat, &$qval, &$ctr, &$prime, &$qnxt)
  {
    $at = current($qat);
    if ($i == $at) {
      array_shift($qat);
      $ctr[] = array_shift($qval);
      $prime = 0;
      $qnxt = current($qat);
    } else {
      print "Misjudged next q element: expected one at $i, found one at $at<br>\n";
    }
  }

  function checknum(&$i, $delta, &$ctr, &$qnxt, &$qat, &$qval, &$primes, $maxroot)
  {
    $i += $delta;

    if ($i == $qnxt) {
      // It's time to get a previously discovered prime off the queue!
      qchk($i, $qat, $qval, $ctr, $prime, $qnxt);
    } else {
      $prime = isprime($i, $ctr);
    }

    if ($prime) {
      $primes[] = $i;
      if ($i <= $maxroot)   // We only have to check against primes up to sqrt( $max )
      {
        // Though we found a prime, it won't be relevant in our
        // checking until we reach its square. Push it on the queue.
        $qat[] = $i * $i;
        $qval[] = $i;
        if ($qnxt == null) $qnxt = $i * $i;
      }
    }
  }

  function findprimes(&$primes, $max, $maxroot)
  {
    $primes = array(2, 3, 5);
    $ctr = array();
    $qat = array();
    $qval = array();
    $qnxt = null;

    //
    // We can ignore 2 and 5, as they are accounted for in
    // the loop below--we skip over any number divisible
    // by 2 or 5.
    //
    $i = 3;
    $ctr[] = $i;

    // Lots of loop unrolling here, so that the set_time_limit()
    // call doesn't have to happen every 5th operation.
    while ($i < $max) {
      set_time_limit(20);

      checknum($i, 4, $ctr, $qnxt, $qat, $qval, $primes, $maxroot);
      checknum($i, 2, $ctr, $qnxt, $qat, $qval, $primes, $maxroot);
      checknum($i, 2, $ctr, $qnxt, $qat, $qval, $primes, $maxroot);
      checknum($i, 2, $ctr, $qnxt, $qat, $qval, $primes, $maxroot);

      checknum($i, 4, $ctr, $qnxt, $qat, $qval, $primes, $maxroot);
      checknum($i, 2, $ctr, $qnxt, $qat, $qval, $primes, $maxroot);
      checknum($i, 2, $ctr, $qnxt, $qat, $qval, $primes, $maxroot);
      checknum($i, 2, $ctr, $qnxt, $qat, $qval, $primes, $maxroot);

      checknum($i, 4, $ctr, $qnxt, $qat, $qval, $primes, $maxroot);
      checknum($i, 2, $ctr, $qnxt, $qat, $qval, $primes, $maxroot);
      checknum($i, 2, $ctr, $qnxt, $qat, $qval, $primes, $maxroot);
      checknum($i, 2, $ctr, $qnxt, $qat, $qval, $primes, $maxroot);

      checknum($i, 4, $ctr, $qnxt, $qat, $qval, $primes, $maxroot);
      checknum($i, 2, $ctr, $qnxt, $qat, $qval, $primes, $maxroot);
      checknum($i, 2, $ctr, $qnxt, $qat, $qval, $primes, $maxroot);
      checknum($i, 2, $ctr, $qnxt, $qat, $qval, $primes, $maxroot);
    }

    print "ctr:<br>\n";
    var_dump($ctr);
    print "<br><br>\n";

    if (count($qat) > 0) {
      print "qat:<br>\n";
      var_dump($qat);
      print "<br><br>\n";
    }

    if (count($qval) > 0) {
      print "qval:<br>\n";
      var_dump($qval);
      print "<br><br>\n";
    }
  }

  $max = 200000;
  $maxroot = (int) floor(sqrt($max));

  findprimes($primes, $max, $maxroot);

  print "Max = $max<br>\n";
  print "Primes Found = " . count($primes) . "<br>\n";

  $chunks = explode(" ", microtime());
  $time_end = $chunks[0] + $chunks[1];
  print "<br><br>Time: $time_end<br>\n";

  //printprimes( $primes );

  ?>

</BODY>

</HTML>
