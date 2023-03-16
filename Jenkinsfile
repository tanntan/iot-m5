pipeline {
  agent any
  stages {
    stage('run build') {
      steps {
        sh './bin/pio run'
      }
    }

    stage('') {
      steps {
        cleanWs(cleanWhenSuccess: true)
      }
    }

  }
}