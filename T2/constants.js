let DOM = document;
DOM.get = DOM.getElementById;

const component = {
    perfButton: DOM.get('performanceTest'),
    steps_show: DOM.get('showStepByStep'),
    steps: DOM.get('StepByStep'),
    inputsContainer: DOM.get('step-inputsContainer'),
    steps_input_array: DOM.get('input1'),
    steps_input_k: DOM.get('input2'),
	error: DOM.get('error'),
	grid: DOM.get('grid'),
	loading: DOM.get('loading')
}

const constants = {
	arraysPerRun: 10,
	arraySizeScale: 1000,
	reRuns: 10,
}

const ViewStates = {
    performance: 'performance',
    stepByStep: 'step-by-step',
}

const global = {
    viewState: ViewStates.performance
}

const regex = {
	hasHide: (testing) => RegExp(/hide/).test(testing),
	onlyNumbers: testing => RegExp(/(e,)|(,e)|(,e{2,1000})|([a-d])|([f-z])/gi).test(testing),
	isANumber: (testing) => RegExp(/(^e$)|e{2,100}|([a-d])|([f-z])/i).test(testing)
}


const SelectionTypes = {
	linear: 'linear',
	sort: 'sort'
}

const HTMLHelper = {
    toggleVisibility: (comp) => {
        const classList = comp.classList;
        if(regex.hasHide(classList.value)) {
            classList.remove('hide');
        } else {
            classList.add('hide');
        }
    },
    hide: (comp) => {
        const classList = comp.classList;
        if(!regex.hasHide(classList.value)) {
            classList.add('hide')
        }
    },
    show: (comp) => {
        const classList = comp.classList;
        if(regex.hasHide(classList.value)) {
            classList.remove('hide')
        }
	},
	resetGrid: () => {
		component.grid.innerHTML = '';	
	}
}
