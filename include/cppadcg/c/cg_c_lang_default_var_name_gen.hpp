#ifndef CPPAD_CG_C_LANG_DEFAULT_VAR_NAME_GEN_INCLUDED
#define CPPAD_CG_C_LANG_DEFAULT_VAR_NAME_GEN_INCLUDED
/* --------------------------------------------------------------------------
 *  CppADCodeGen: C++ Algorithmic Differentiation with Source Code Generation:
 *    Copyright (C) 2012 Ciengis
 *
 *  CppADCodeGen is distributed under multiple licenses:
 *
 *   - Common Public License Version 1.0 (CPL1), and
 *   - GNU General Public License Version 2 (GPL2).
 *
 * CPL1 terms and conditions can be found in the file "epl-v10.txt", while
 * terms and conditions for the GPL2 can be found in the file "gpl2.txt".
 * ----------------------------------------------------------------------------
 * Author: Joao Leal
 */

namespace CppAD {

    /**
     * Creates variables names for the source code.
     * 
     * @author Joao Leal
     */
    template<class Base>
    class CLangDefaultVariableNameGenerator : public VariableNameGenerator<Base> {
    protected:
        // auxiliary string stream
        std::stringstream _ss;
        // array name of the dependent variables
        std::string _depName;
        // array name of the independent variables
        std::string _indepName;
        // array name of the temporary variables
        std::string _tmpName;
        // array name of the temporary array variables
        std::string _tmpArrayName;
        // the lowest variable ID used for the temporary variables
        size_t _minTemporaryID;
        // the highest variable ID used for the temporary variables
        size_t _maxTemporaryID;
        // the highest ID used for the temporary array variables
        size_t _maxTemporaryArrayID;
    public:

        inline CLangDefaultVariableNameGenerator() :
            _depName("y"),
            _indepName("x"),
            _tmpName("var"),
            _tmpArrayName("array") {
            this->_independent.push_back(FuncArgument(_indepName));
            this->_dependent.push_back(FuncArgument(_depName));
            this->_temporary.push_back(FuncArgument(_tmpName));
            this->_temporary.push_back(FuncArgument(_tmpArrayName));
        }

        inline CLangDefaultVariableNameGenerator(const std::string& depName,
                                                 const std::string& indepName,
                                                 const std::string& tmpName,
                                                 const std::string& tmpArrayName) :
            _depName(depName),
            _indepName(indepName),
            _tmpName(tmpName),
            _tmpArrayName(tmpArrayName) {
            this->_independent.push_back(FuncArgument(_indepName));
            this->_dependent.push_back(FuncArgument(_depName));
            this->_temporary.push_back(FuncArgument(_tmpName));
            this->_temporary.push_back(FuncArgument(_tmpArrayName));
        }

        inline virtual size_t getMinTemporaryVariableID() const {
            return _minTemporaryID;
        }

        inline virtual size_t getMaxTemporaryVariableID() const {
            return _maxTemporaryID;
        }

        inline virtual size_t getMaxTemporaryArrayVariableID() const {
            return _maxTemporaryArrayID;
        }

        inline virtual std::string generateDependent(size_t index) {
            _ss.clear();
            _ss.str("");

            _ss << _depName << "[" << index << "]";

            return _ss.str();
        }

        inline virtual std::string generateIndependent(const OperationNode<Base>& independent) {
            _ss.clear();
            _ss.str("");

            size_t id = independent.getVariableID();
            _ss << _indepName << "[" << (id - 1) << "]";

            return _ss.str();
        }

        inline virtual std::string generateTemporary(const OperationNode<Base>& variable) {
            _ss.clear();
            _ss.str("");

            size_t id = variable.getVariableID();
            if (this->_temporary[0].array) {
                _ss << _tmpName << "[" << (id - this->_minTemporaryID) << "]";
            } else {
                _ss << _tmpName << id;
            }

            return _ss.str();
        }

        virtual std::string generateTemporaryArray(const OperationNode<Base>& variable) {
            _ss.clear();
            _ss.str("");

            assert(variable.getOperationType() == CGArrayCreationOp);

            size_t id = variable.getVariableID();
            _ss << "&" << _tmpArrayName << "[" << (id - 1) << "]";

            return _ss.str();
        }

        virtual std::string generateIndexedDependent(const OperationNode<Base>& var,
                                                     const IndexPattern& ip) {
            CPPADCG_ASSERT_KNOWN(var.getOperationType() == CGLoopIndexedDepOp, "Invalid node type");
            CPPADCG_ASSERT_KNOWN(!var.getArguments().empty(), "Invalid number of arguments");

            _ss.clear();
            _ss.str("");

            _ss << _depName << "[" << CLanguage<Base>::indexPattern2String(ip, getIndexes(var, 1)) << "]";

            return _ss.str();
        }

        virtual std::string generateIndexedIndependent(const OperationNode<Base>& independent,
                                                       const IndexPattern& ip) {
            CPPADCG_ASSERT_KNOWN(independent.getOperationType() == CGLoopIndexedIndepOp, "Invalid node type");
            CPPADCG_ASSERT_KNOWN(independent.getArguments().size() > 0, "Invalid number of arguments");

            _ss.clear();
            _ss.str("");

            _ss << _indepName << "[" << CLanguage<Base>::indexPattern2String(ip, getIndexes(independent, 0)) << "]";

            return _ss.str();
        }

        inline virtual void setTemporaryVariableID(size_t minTempID, size_t maxTempID, size_t maxTempArrayID) {
            _minTemporaryID = minTempID;
            _maxTemporaryID = maxTempID;
            _maxTemporaryArrayID = maxTempArrayID;

            // if
            //  _minTemporaryID == _maxTemporaryID + 1
            // then no temporary variables are being used
            assert(_minTemporaryID <= _maxTemporaryID + 1);
        }

        inline virtual ~CLangDefaultVariableNameGenerator() {
        }
    protected:

        static inline std::vector<const IndexDclrOperationNode<Base>*> getIndexes(const OperationNode<Base>& var, size_t offset) {
            const std::vector<Argument<Base> >& args = var.getArguments();
            std::vector<const IndexDclrOperationNode<Base>*> indexes(args.size() - offset);

            for (size_t a = offset; a < args.size(); a++) {
                CPPADCG_ASSERT_KNOWN(args[a].getOperation() != NULL, "Invalid argument");
                CPPADCG_ASSERT_KNOWN(args[a].getOperation()->getOperationType() == CGIndexOp, "Invalid argument");

                indexes[a - offset] = &static_cast<const IndexOperationNode<Base>*> (args[a].getOperation())->getIndex();
            }

            return indexes;
        }
    };
}

#endif
