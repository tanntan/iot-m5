pipeline {
  agent any
  stages {
    stage('build') {
      steps {
        sh 'sudo apt-get update'
      }
    }

    stage('run build') {
      steps {
        sh './bin/pio run'
      }
    }

  }
}