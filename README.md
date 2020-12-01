# ComplexCalculator

* 通过C语言实现的一个简单计算器，拥有**简单模式**和**复杂模式**两种功能，整个系统拥有如下特点：
  1. 系统用**枚举**和**函数指针数组**结合**结构体**实现状态机架构
  2. 构建**datacenter数据中心**用来在模块之间传递数据，实现**高内聚，低耦合**
  3. 系统采用**匈牙利法**编程风格
  4. 简单模式可以实现数值运算（加、减、乘、除）
  5. 复杂模式可以求班级学生信息的（平均值、方差），学生信息格式，姓名、语文、数学、英语成绩
* 这个小项目代码量在**2500左右**，是我刚学习C语言时候做的，特别适合新手刚学习完C语言，用来巩固提高，其中设计的**编码规划**和**程序架构**还是有可以值得借鉴的地方，但是该项目本身也还有一些不足，后面我还会做一些的简单的优化，也欢迎大家提出意见！

## 模块说明

* CalcComplexMain：主函数，调用主状态机
* CalcExe：计算模块
* CalcInput：输入处理模块
* CalcOutput：输出处理模块
* CalcState：状态机实现，以下是状态机核心代码说明

```C
/*Main state machine state declaration */
typedef enum {
    CALCSTATE_INIT = 0,
    CALCSTATE_MODESELECT,
    CALCSTATE_RUNNING,
    CALCSTATE_WAIT,
    CALCSTATE_EXIT,
    CALCSTATE_INVALID,
} CalcState_e;

/*calculator simple mode state machine state declaration*/
typedef enum {
    SIMPCALCSTATE_INIT = 0,
    SIMPCALCSTATE_INPUT_1ST,
    SIMPCALCSTATE_INPUT_OPERATOR,
    SIMPCALCSTATE_INPUT_2ND,
    SIMPCALCSTATE_CALCEXE,
    SIMPCALCSTATE_PRINTRESULT,
    SIMPCALCSTATE_WAIT,
    SIMPCALCSTATE_EXIT,
    SIMPCALCSTATE_INVALID,
} SimpCalcState_e;

/*calculator complex mode state machine state declaration*/
typedef enum {
    COMPCALCSTATE_INIT = 0,
    COMPCALCSTATE_INPUTMENU,
    COMPCALCSTATE_INPUTSTUDENTINFO,
    COMPCALCSTATE_PRINTSTUDENTINFO,
    COMPCALCSTATE_CALCAVERAGE,
    COMPCALCSTATE_CALCVARIANCE,
    COMPCALCSTATE_PRINTAVERAGE,
    COMPCALCSTATE_PRINTVARIANCE,
    COMPCALCSTATE_EXIT,
    COMPCALCSTATE_FAIL,
    COMPCALCSTATE_INVALID,
} CompCalcState_e;

/*action function about the major state machine*/
int CalcState_Init(int iState);
int CalState_UserModeSelect(int iState);
int CalcState_Running(int iState);
int CalcState_Wait(int iState);
int CalcState_Exit(int iState);

/*action function about the calculator simple mode state machine*/
void SimCalcState_Main(void);
int SimCalcState_Init(int iState);
int SimCalState_Input1stNum(int iState);
int SimCalState_Input_Operator(int iState);
int SimCalState_Input2stNum(int iState);
int SimCalState_Calculating(int iState);
int SimCalState_CalcDone(int iState);
int SimCalState_Wait(int iState);
int SimCalState_Exit(int state);

/*action function about the calculator complex mode state machine*/
void CompCalcState_Main(void);
int ComCalcState_Init(int iState);
int ComCalcState_InputMenu(int iState);
/*selcec the calculator statistical*/
int ComCalcState_StatMethodSel(char * cpcStatMethod);
int ComCalcState_StatMethodSelISI(int iState);
int ComCalcState_StatMethodSelPSI(int iState);
int ComCalcState_StatMethodSelCA(int iState);
int ComCalcState_StatMethodSelCV(int iState);
int ComCalcState_StatMethodSelPA(int iState);
int ComCalcState_StatMethodSelPV(int iState);
int ComCalcState_StatMethodSelE(int iState);
int ComCalcState_StatMethodSelFail(int iState);

typedef struct StateControl_t_ {
    int iCurState;
    int (* pfDoCurState[])(int iState);
} StateControl_t;

/*Initialize the main state machine*/
StateControl_t g_stCalcState = {
    CALCSTATE_INIT,
    {
        CalcState_Init,
        CalState_UserModeSelect,
        CalcState_Running,
        CalcState_Wait,
        CalcState_Exit,
    },
};

/*Initialize the calculator simple mode state machine*/
StateControl_t g_stSimpCalcState = {
    SIMPCALCSTATE_INIT,
    {
        SimCalcState_Init,
        SimCalState_Input1stNum,
        SimCalState_Input_Operator,
        SimCalState_Input2stNum,
        SimCalState_Calculating,
        SimCalState_CalcDone,
        SimCalState_Wait,
        SimCalState_Exit,
    },
};

/*Initialize the calculator complex mode state machine*/
StateControl_t g_stCompCalcState = {
    SIMPCALCSTATE_INIT,
    {
        ComCalcState_Init,
        ComCalcState_InputMenu,
        ComCalcState_StatMethodSelISI,
        ComCalcState_StatMethodSelPSI,
        ComCalcState_StatMethodSelCA,
        ComCalcState_StatMethodSelCV,
        ComCalcState_StatMethodSelPA,
        ComCalcState_StatMethodSelPV,
        ComCalcState_StatMethodSelE,
        ComCalcState_StatMethodSelFail,
    },
};

/************************************************************
 * FUNCTION:CalcState_Main()
 * Description:Main state machine control
 * Arguments:void
 * return:void
 * *********************************************************/
void CalcState_Main(void)
{
    while (g_stCalcState.iCurState != CALCSTATE_INVALID)
    {
        g_stCalcState.iCurState = g_stCalcState.pfDoCurState[g_stCalcState.iCurState](g_stCalcState.iCurState);
    };
	
    g_stCalcState.iCurState = CALCSTATE_INIT;
}

/************************************************************
 * FUNCTION   :SimCalcState_Main()
 * Description:The main state machine control of the 
 *             calculator working in simple mode
 * Arguments  :void
 * return     :void
 * *********************************************************/
void SimCalcState_Main(void)
{
    while (g_stSimpCalcState.iCurState != SIMPCALCSTATE_INVALID)
    {
        g_stSimpCalcState.iCurState = g_stSimpCalcState.pfDoCurState[g_stSimpCalcState.iCurState](g_stSimpCalcState.iCurState);
    };
    g_stSimpCalcState.iCurState = SIMPCALCSTATE_INIT;
}

/************************************************************
 * FUNCTION   :CompCalcState_Main()
 * Description:State machine control of calculator working 
 *             in complex mode
 * Arguments  :void
 * return     :void
 * *********************************************************/
void CompCalcState_Main(void)
{
    while (g_stCompCalcState.iCurState != COMPCALCSTATE_INVALID)
    {
        g_stCompCalcState.iCurState = g_stCompCalcState.pfDoCurState[g_stCompCalcState.iCurState](g_stCompCalcState.iCurState);
    };
    g_stCompCalcState.iCurState = COMPCALCSTATE_INIT;
}
```

* DataCenter：数据中心

## 程序流程图
![流程图](https://github.com/dadatuYHD/ComplexCalculator/blob/master/Picture/%E6%B5%81%E7%A8%8B%E5%9B%BE.png)

