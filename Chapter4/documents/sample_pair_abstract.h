//This object is intended to represent an edge in an undirected graph which has data samples at its vertices. 
//Therefore, it is the undirected version of ordered_sample_pair.


//Check : http://dlib.net/graph_tools.html#sample_pair



    class sample_pair 
    {
        /*!
            WHAT THIS OBJECT REPRESENTS
                This object is intended to represent an edge in an undirected graph 
                which has data samples at its vertices.  So it contains two integers
                (index1 and index2) which represent the identifying indices of 
                the samples at the ends of an edge.  Note that this object enforces
                the constraint that index1 <= index2.  This has the effect of 
                making the edges undirected since a sample_pair is incapable
                of representing a single edge in more than one way.  That is,
                sample_pair(i,j) == sample_pair(j,i) for any value of i and j.

                This object also contains a double which can be used for any purpose.
        !*/

    public:
        sample_pair(
        );
        /*!
            ensures
                - #index1() == 0
                - #index2() == 0
                - #distance() == 1 
        !*/

        sample_pair (
            const unsigned long idx1,
            const unsigned long idx2
        );
        /*!
            ensures
                - #index1() == min(idx1,idx2)
                - #index2() == max(idx1,idx2)
                - #distance() == 1 
        !*/

        sample_pair (
            const unsigned long idx1,
            const unsigned long idx2,
            const double dist
        );
        /*!
            ensures
                - #index1() == min(idx1,idx2)
                - #index2() == max(idx1,idx2)
                - #distance() == dist
        !*/

        const unsigned long& index1 (
        ) const; 
        /*!
            ensures
                - returns the first index value stored in this object 
        !*/

        const unsigned long& index2 (
        ) const; 
        /*!
            ensures
                - returns the second index value stored in this object 
        !*/

        const double& distance (
        ) const;
        /*!
            ensures
                - returns the floating point number stored in this object
        !*/

    };

// ----------------------------------------------------------------------------------------

    template <typename T>
    bool order_by_index (
        const T& a,
        const T& b
    ) { return a.index1() < b.index1() || (a.index1() == b.index1() && a.index2() < b.index2()); }
    /*!
        requires
            - T is a type with an interface compatible with sample_pair.
        ensures
            - provides a total ordering of sample_pair objects that will cause pairs that are 
              equal to be adjacent when sorted.  So for example, this function can be used
              with std::sort() to first sort a sequence of sample_pair objects and then
              find duplicate edges.
    !*/
