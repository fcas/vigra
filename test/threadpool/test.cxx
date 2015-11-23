/************************************************************************/
/*                                                                      */
/*        Copyright 2014-2015 by Ullrich Koethe and Philip Schill       */
/*                                                                      */
/*    This file is part of the VIGRA computer vision library.           */
/*    The VIGRA Website is                                              */
/*        http://hci.iwr.uni-heidelberg.de/vigra/                       */
/*    Please direct questions, bug reports, and contributions to        */
/*        ullrich.koethe@iwr.uni-heidelberg.de    or                    */
/*        vigra@informatik.uni-hamburg.de                               */
/*                                                                      */
/*    Permission is hereby granted, free of charge, to any person       */
/*    obtaining a copy of this software and associated documentation    */
/*    files (the "Software"), to deal in the Software without           */
/*    restriction, including without limitation the rights to use,      */
/*    copy, modify, merge, publish, distribute, sublicense, and/or      */
/*    sell copies of the Software, and to permit persons to whom the    */
/*    Software is furnished to do so, subject to the following          */
/*    conditions:                                                       */
/*                                                                      */
/*    The above copyright notice and this permission notice shall be    */
/*    included in all copies or substantial portions of the             */
/*    Software.                                                         */
/*                                                                      */
/*    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND    */
/*    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES   */
/*    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND          */
/*    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT       */
/*    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,      */
/*    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING      */
/*    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR     */
/*    OTHER DEALINGS IN THE SOFTWARE.                                   */
/*                                                                      */
/************************************************************************/
#include <vigra/unittest.hxx>
#include <vigra/threadpool.hxx>
#include <numeric>

using namespace vigra;

struct ThreadPoolTests
{
    void test_threadpool()
    {
        size_t const n = 10000;
        std::vector<int> v(n);
        ThreadPool pool(4);
        for (size_t i = 0; i < v.size(); ++i)
        {
            pool.enqueue(
                [&v, i](size_t thread_id)
                {
                    v[i] = 0;
                    for (size_t k = 0; k < i+1; ++k)
                    {
                        v[i] += k;
                    }
                }
            );
        }
        pool.waitFinished();

        std::vector<int> v_expected(n);
        for (size_t i = 0; i < v_expected.size(); ++i)
        {
            v_expected[i] = i*(i+1)/2;
        }
        shouldEqualSequence(v.begin(), v.end(), v_expected.begin());
    }

    void test_parallel_foreach()
    {
        size_t const n = 10000;
        std::vector<int> v_in(n);
        std::iota(v_in.begin(), v_in.end(), 0);
        std::vector<int> v_out(n);
        parallel_foreach(4, n, v_in.begin(), v_in.end(),
            [&v_out](size_t thread_id, int x)
            {
                v_out[x] = x*(x+1)/2;
            }
        );

        std::vector<int> v_expected(n);
        for (size_t i = 0; i < v_expected.size(); ++i)
        {
            v_expected[i] = i*(i+1)/2;
        }
        shouldEqualSequence(v_out.begin(), v_out.end(), v_expected.begin());
    }
};

struct ThreadPoolTestSuite : public test_suite
{
    ThreadPoolTestSuite()
        :
        test_suite("ThreadPool test")
    {
        add(testCase(&ThreadPoolTests::test_threadpool));
        add(testCase(&ThreadPoolTests::test_parallel_foreach));
    }
};

int main(int argc, char** argv)
{
    ThreadPoolTestSuite threadpool_test;
    int failed = threadpool_test.run(testsToBeExecuted(argc, argv));
    std::cout << threadpool_test.report() << std::endl;
    return (failed != 0);
}