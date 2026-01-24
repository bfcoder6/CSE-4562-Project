## CSE 4/562 - Checkpoint 1

We have extensively tested the source code in the lab distribution but there
could inevitably be bugs as in any project. To report a BUG, please post a
**private** message in the Piazza to all TA and the
instructor. It will made public once validated. Please refer to the course
website for the policy of getting extra credit for successful reporting of
bugs.

#### Overview

In this checkpoint, you will:
- Learn the POSIX file API
- Learn the testing suite
- Establish your Journal.
- Familiarize yourself with the submission process.

#### Resources

* [This Readme](https://git.odin.cse.buffalo.edu/CSE-4562/2026-sp-project/src/branch/checkpoint-1/docs/CHECKPOINT-1.md)
* [Autolab Submission](https://autolab.cse.buffalo.edu/courses/cse462-s26/assessments/Checkpoint-1-POSIX-IO)

You are also encouraged to review the `man` (manual) pages, which you can access from almost any linux terminal.  For example, to look up the documentation for `fopen(2)`, I would type `man 2 fopen` (i.e., the manual page from section `2` for `fopen`).  

#### Academic Integrity and Generative AI

As a reminder, the use of Generative AI is **not** permitted for the creation of any course deliverables.

Remember that you will be evaluated on your understanding of the code that you (as a group) have written.  Your entire group should be able to:
1. Understand the design decisions that you had to make in implementing the project.
2. Be able to explain the design space of all such decisions.
3. Be ready to discuss assumptions you made in developing the code, and your strategy for overcoming them.

Generative AI tools have been shown to increase their user's confidence, without a corresponding increase in productivity.  In short, GenAI eliminates forcing functions for lack of understanding, in turn making it harder to properly gauge whether you understand the problem.  2/3 of your project grade comes from your ability to discuss your code and its evolution, so keep that in mind when considering any risk/reward trade-offs.

As noted in the syllabus, you may wthdraw any submission at any time for any reason, prior to course staff becoming aware of an AI violation.  See the amnesty policy in the syllabus for details.

#### Journaling

Starting with this assignment, your team is expected to maintain a dev journal.  Everyone should collaboratively edit the same document.  The format is open-ended, but should contain at least:

- A brief overview of the problem.  In your own words what are your objectives, and how do you determine whether you have met them?
- A brief overview of the design space.  What problems will you need to solve?  How do you plan to approach them?  What questions do you need to answer?
- A log of your failed attempt at passing the test cases.

This last item deserves a little more discussion.  **If running the tests (e.g. `make -C build test`) results in a failing test**, do not just go back to writing code.

Stop.  Think.

(this also applies if you're hitting a compiler error that you don't understand)

First, write down what the error is.  What is the code doing, and what *should* the code be doing instead?

Second, write down a plan to tackle the error.  This can include:
- One or more hypotheses about why the error is happening, along with proposed ways to test the hypothesis and/or fix it.
- Working backwards from where the error is happening, what is the latest stage where you can confidently state that the code is behaving correctly.
- Working backwards from where the error is happening, where are points in the code where you can easily check whether the code is behaving correctly.  For example:
    - Are function inputs what you expect them to be?
    - Is data being written out to disk correctly?
    - What is the state of the data structure that you are presently manipulating.

Once you've jotted down an *initial* plan, now you can go back to coding.  You've just jotted down a few ideas, so now test them.  Instrument your code.  Use `gdb` or another debugger.  As you learn more, write it down.  You may need to revise your hypotheses, but add them; don't delete the old ones.

Once you understand what the underlying problem is, write that down as well (even if it's a few words confirming a hypothesis you've already stated).

>   Good decisions come from experience.
>   Experience comes from making bad decisions.
> 
>   - [Inspirational Skeletor](https://mas.to/@skeletor/115945540203989184)

You will absolutely, 100%, make dumb mistakes.  I did.  Document them all.  Here's a brief excerpt from my journal in case you don't believe me:

```md
#### Reading is important

I misread the `Read`/`Write` spec.  My original implementation attempted to resolve partially reads/writes, rather than triggering a failure per the spec.  I fixed this, coupled with a bit of simplification on the error handling logic.  

#### File size

A slight misinterpretation of the spec: I assumed that once a file was opened, it would be untouched by other operations.  Per the spec, the file will not be touched *whille* it is open.  Fixing this required me to re-cache the file size when `Reopen`ing.

#### Close Error Handling

I wasn't doing error handling properly in close.  Unfortunately, the way the test case caught this was in its check for "Double Close".  This led me down a frustrating search through the spec and my code for why `Close` wasn't properly updating the file descriptor.  I eventually had a closer look at the test cases to discover that they were not calling `Close()` twice, as I had assumed, but rather playing some file-descriptor tricks to close the FD behind my back.  This clarified that the actual problem with my code was a lack of error checking, and I was able to fix it.

```

#### Setup

One member of your team should merge in code for Checkpoint 1.  Assuming you ran the setup script for checkpoint 0, you should be able to update your main repository as follows:

```sh
git fetch project
git merge project/checkpoint-1
git push
```

Refer to the Checkpoint 0 instructions (see `docs/CHECKPOINT-0.md`) for information on how to build your repository, and run tests.


#### Project

A skeleton implementation of `taco::FSFile` is provided in:
- `include/storage/FSFile.h`
- `src/storage/FSFile.cpp`

Complete the `FSFile` interface.  Specifications for each function may be found in the header file, while the source file includes some hints for where to look for documentation.  Remember the `man` pages.

A new suite of test cases has been added to your repository.  Building your project will produce `bin/BasicTestFSFile` in your build directory, or you may use `make` or `ctest` as outlined in the Checkpoint 0 instructions.  You are encouraged to review the source code for the test cases, which may be found in `tests/storage/BasicTestFSFile.cpp`.

**You are receiving all test cases for this project.**

If you pass tests on your computer (in a timely manner), it is highly likely that you will also pass them on autolab.  Note that autolab *will* replace your test case implementations with its own, so you are discouraged from modifying the test cases directly.  Also remember that you will be called on to explain your code.  Good luck!

#### Submission

1. Ensure that your code passes all test cases
2. Ensure that your repository is properly committed.
3. Convert your journal into a PDF (`pandoc` generates nice-looking PDFs from markdown files)
4. Upload your journal PDF as the submittable in autolab.
5. Wait for autolab to confirm that your code passes test cases.
6. Schedule a meeting with me (see [Piazza](https://piazza.com/buffalo/spring2026/cse4562) for my scheduler).

Once you upload your journal, Autolab will fetch your repository and ensure that it is able to successfully run the test suite. 
